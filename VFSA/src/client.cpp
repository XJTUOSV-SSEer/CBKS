#include "../include/client.h"
#include "../include/Twin_BloomFilter.h"
#include "../include/MerkleTree.h"
#include "../include/MultisetAccumulator.h"
#include "../include/BigInteger.h"
#include <iostream>



client::client(int num_of_hashs,int len_of_bf){
    this->num_of_hashs=num_of_hashs;
    this->len_of_bf=len_of_bf;

    // 创建累加器MSA
    MultisetAccumulator msa;
    this->msa=msa;

    


}



MerkleTree client::index_gen(std::vector<std::pair<std::string,std::set<std::string>>> dataset){
    // 创建merkle树
    MerkleTree mkt(len_of_bf,num_of_hashs,msa);

    // 处理每个文件，生成merkle树的所有叶结点
    for(int i=0;i<dataset.size();i++){
        // 文件id
        std::string f_id=dataset[i].first;
        // 关键字集合
        std::set<std::string> w_set=dataset[i].second;

        // 对每个文件，生成一个merkle树的叶结点，然后计算对应的tbf,acc,P_T
        struct node leaf(len_of_bf,num_of_hashs);
        leaf.f_id=f_id;
        leaf.is_leaf=true;

        // 计算tbf
        for(std::set<std::string>::iterator it=w_set.begin();it!=w_set.end();it++){
            std::string w=(*it);
            // 将关键字加入tbf
            leaf.tbf.add(w);
        }

        // 计算P_T
        leaf.P_T=msa.get_product(w_set);

        // 计算acc
        leaf.acc=msa.get_acc(w_set);

        // 计算digest
        leaf.get_leaf_digest();

        // 将叶结点加入merkle树
        mkt.tree.push_back(leaf);
    }

    // 使用merkle树的所有叶结点，自顶向下的构建merkle树
    mkt.construct_tree();

    // 保存根哈希
    this->root_hash=mkt.tree[mkt.root_id].digest;

    return mkt;
}


struct trapdoor client::trap_gen(std::string w){
    struct trapdoor msg;

    // 计算w对应的素数
    BigInteger bi;
    BigInteger::generate_prime(bi,w);
    msg.x=bi.to_string();

    // 计算k个位置
    Twin_BloomFilter tbf(len_of_bf,num_of_hashs);
    for(int i=0;i<num_of_hashs;i++){
        int loc=tbf.get_h_i(w,i);
        msg.locs.push_back(loc);
    }

    return msg;
}



void client::verify_result(std::string w,struct query_result qr){
    // merkle proove
    // qr.res[0].acc="1";           // 随机编造acc
    std::string hash=MerkleTree::merkle_proove(qr);
    // 与本地保存的根哈希对比
    if(hash!=(this->root_hash)){
        std::cout<<"Merkle Proove wrong"<<std::endl;
        return;
    }


    std::vector<struct proof_node>& res=qr.res;
    for(int i=0;i<res.size();i++){
        struct proof_node& pn = res[i];
        // 验证匹配的叶结点,判断关键字是否真正存在
        if(pn.is_match && pn.is_leaf){
            if(pn.tbf.verify(w)==false){
                std::cout<<"the file doesn't contain w"<<std::endl;
                return;
            }
            else{
                std::cout<<pn.f_id<<std::endl;
            }
        }


        // 验证不匹配的结点
        if(!pn.is_match){
            // pn.pi.d="123128018203";      // 编造pi
            if(msa.verify_nonmembership(pn.acc,pn.pi,w)==false){
                std::cout<<"nonmembership verify error"<<std::endl;
                return;
            }
        }
        
    }

}