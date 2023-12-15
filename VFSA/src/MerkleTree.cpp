#include "../include/MerkleTree.h"
#include "../include/MultisetAccumulator.h"
#include "../include/BigInteger.h"
#include<set>
#include<queue>



MerkleTree::MerkleTree(int len_of_bf,int num_of_hashs,MultisetAccumulator msa){
    this->len_of_bf=len_of_bf;
    this->num_of_hashs=num_of_hashs;
    this->msa=msa;
}


void MerkleTree::construct_tree(){
    // 使用队列储存叶结点在tree数组中的下标
    std::queue<int> leaf_set;
    for(int i=0;i<tree.size();i++){
        leaf_set.push(i);
    }

    // 构建merkle树
    this->root_id=sub_tree(leaf_set);
}



int MerkleTree::sub_tree(std::queue<int> leaf_set){
    // 递归边界
    // 判断leaf_set中是否只有1个元素。
    // 若只有一个元素，则直接返回该叶结点的id
    int n=leaf_set.size();
    if(n==1){
        int root_id=leaf_set.front();
        return root_id;
    }

    // 递归表达式，处理非叶结点
    // 首先将leaf_set分为两个子集
    int l_num=(n+1)/2;
    int r_num=n-l_num;

    // 左子树的集合
    std::queue<int> l_set;
    for(int i=0;i<l_num;i++){
        int id=leaf_set.front();
        l_set.push(id);
        leaf_set.pop();
    }

    // 构建左、右子树
    int lchild_id=sub_tree(l_set);
    int rchild_id=sub_tree(leaf_set);

    // 生成该子树的root结点
    struct node root(len_of_bf,num_of_hashs);
    root.is_leaf=false;
    root.lchild=lchild_id;
    root.rchild=rchild_id;

    // tbf计算
    root.tbf.merge(tree[lchild_id].tbf,tree[rchild_id].tbf);

    // P_T计算。直接左右子节点的product相乘（有重复元素是不影响的）
    BigInteger product_l(tree[lchild_id].P_T);
    BigInteger product_r(tree[rchild_id].P_T);
    BigInteger product;
    BigInteger::mul(product,product_l,product_r);
    root.P_T=product.to_string();


    // acc计算
    std::set<std::string> w_set;
    root.acc=(this->msa).get_acc(root.P_T);


    // digest
    root.get_nonleaf_digest(tree[lchild_id].digest,tree[rchild_id].digest);

    // root结点构建完成，加入tree数组
    (this->tree).push_back(root);

    // 返回在tree数组中的下标
    return (this->tree).size()-1;
}


struct query_result MerkleTree::query(std::string& x,std::vector<int>& locs){
    struct query_result qr;
    std::vector<struct proof_node>& res=qr.res;

    // 对merkle树进行DFS
    qr.root_id=DFS_query(this->root_id,x,locs,res);

    return qr;
}



int MerkleTree::DFS_query(int id,std::string& x,std::vector<int>& locs,std::vector<struct proof_node>& res){    
    // 判断关键字是否匹配
    // 当前merkle树结点n
    struct node& n=tree[id];
    bool is_match=true;
    for(int i=0;i<locs.size();i++){
        int loc=locs[i];
        int cell=n.tbf.get_chosen_cell(loc);
        bool value=n.tbf.get_value(loc,cell);
        if(!value){
            is_match=false;
            break;
        }
    }

    // 构造1个proof_node
    struct proof_node pn(n.tbf);


    // 结点匹配
    if(is_match){

        // 是叶结点
        if(n.is_leaf){
            pn.f_id=n.f_id;
            pn.is_match=true;
            pn.is_leaf=true;
            pn.acc=n.acc;
            pn.lchild=-1;
            pn.rchild=-1;
        }


        // 是非叶结点
        else{
            pn.is_match=true;
            pn.is_leaf=false;
            pn.acc=n.acc;
            
            // 递归处理左,右子结点，得到左右子结点在res数组中的下标
            int l_pn_id=DFS_query(n.lchild,x,locs,res);
            int r_pn_id=DFS_query(n.rchild,x,locs,res);

            pn.lchild=l_pn_id;
            pn.rchild=r_pn_id;
        }
    }

    // 结点不匹配
    else{
        // 是叶结点
        if(n.is_leaf){
            pn.f_id=n.f_id;
            pn.is_match=false;
            pn.is_leaf=true;
            pn.acc=n.acc;

            // 不相交证明
            pn.pi=msa.proove_nonmembership_prime(n.P_T,x);

            pn.lchild=-1;
            pn.rchild=-1;
        }
        

        // 是非叶结点
        else{
            pn.is_match=false;
            pn.is_leaf=false;
            pn.acc=n.acc;
            pn.pi=msa.proove_nonmembership_prime(n.P_T,x);

            // 计算H(lchild.d||rchild.d)
            char tmp[SHA256_SIZE*2];
            Crypto_Primitives::string2char(tree[n.lchild].digest,tmp);
            Crypto_Primitives::string2char(tree[n.rchild].digest,tmp+SHA256_SIZE);
            char buf[SHA256_SIZE];
            int digest_len;
            Crypto_Primitives::SHA256_digest((unsigned char*)tmp,SHA256_SIZE*2,
                    (unsigned char*)buf,(unsigned int*)&digest_len);
            pn.child_digest=std::string(buf,SHA256_SIZE);
        }
    }


    // 将proof_node结点加入res数组
    res.push_back(pn);
    return res.size()-1;
}



std::string MerkleTree::merkle_proove(struct query_result qr){
    // 计算根哈希
    get_root_hash(qr.root_id,qr.res);

    return qr.res[qr.root_id].digest;
}



void MerkleTree::get_root_hash(int id,std::vector<struct proof_node>& res){
    struct proof_node& pn=res[id];
    // 判断结点是否为叶结点

    // 是叶结点
    if(pn.is_leaf){
        // 计算H(tbf||acc)
        std::string tbf_str=pn.tbf.to_string();
        std::string s=tbf_str+pn.acc;
        int len=s.length();
        char* buf=new char[len];
        Crypto_Primitives::string2char(s,buf);

        char d[SHA256_SIZE];
        int digest_len;
        Crypto_Primitives::SHA256_digest((unsigned char*)buf,len,(unsigned char*)d,(unsigned int*)&digest_len);
        pn.digest=std::string(d,SHA256_SIZE);
    }

    
    // 不是叶结点
    else{
        // 匹配,需要递归调用
        if(pn.is_match){
            // 获取左、右子节点的digest
            get_root_hash(pn.lchild,res);
            get_root_hash(pn.rchild,res);

            // 计算H(lchild.d||rchild.d)
            std::string lchild_digest=res[pn.lchild].digest;
            std::string rchild_digest=res[pn.rchild].digest;
            char tmp1[SHA256_SIZE*2];       // lchild.d||rchild.d
            Crypto_Primitives::string2char(lchild_digest,tmp1);
            Crypto_Primitives::string2char(rchild_digest,tmp1+SHA256_SIZE);
            char tmp2[SHA256_SIZE];         // 储存H(lchild.d||rchild.d)
            int digest_len;
            Crypto_Primitives::SHA256_digest((unsigned char*)tmp1,SHA256_SIZE*2,(unsigned char*)tmp2,
                        (unsigned int*)&digest_len);
            

            std::string tbf_str=pn.tbf.to_string();
            std::string s=tbf_str+pn.acc;
            int len=s.length();
            char* buf=new char[len+SHA256_SIZE];            // 储存H(lchild.d||rchild.d)||tbf||acc
            memcpy(buf,tmp2,SHA256_SIZE);
            Crypto_Primitives::string2char(s,buf+SHA256_SIZE);

            // 求digest
            char ret[SHA256_SIZE];
            Crypto_Primitives::SHA256_digest((unsigned char*)buf,SHA256_SIZE+len,
                                            (unsigned char*)ret,(unsigned int*)&digest_len);
            
            pn.digest=std::string(ret,SHA256_SIZE);


            delete[] buf;
        }


        // 不匹配
        else{
            std::string tbf_str=pn.tbf.to_string();
            std::string s=tbf_str+pn.acc;                   // tbf||acc
            int len=s.length();
            char* buf=new char[len+SHA256_SIZE];            // 储存H(lchild.d||rchild.d)||tbf||acc
            Crypto_Primitives::string2char(pn.child_digest,buf);
            Crypto_Primitives::string2char(s,buf+SHA256_SIZE);

            // 求digest
            char ret[SHA256_SIZE];
            int digest_len;
            Crypto_Primitives::SHA256_digest((unsigned char*)buf,SHA256_SIZE+len,
                                            (unsigned char*)ret,(unsigned int*)&digest_len);
            
            pn.digest=std::string(ret,SHA256_SIZE);

            delete[] buf;
        }
    }
}