#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <vector>
#include<queue>
#include "Twin_BloomFilter.h"
#include "Crypto_Primitives.h"
#include "MultisetAccumulator.h"
#include "data_type.h"
#include "msg.h"

/*
    merkle树的结点
*/
struct node{
    // 文件名。叶结点会填充该字段
    std::string f_id;
    // 表示是否为叶结点
    bool is_leaf;
    // TBF
    Twin_BloomFilter tbf;
    // P(T)，即x_p
    std::string P_T;
    // acc
    std::string acc;
    // digest
    // 对于叶结点，digest=H(tbf||acc)
    // 对于非叶结点，digest=H(H(lchild.d||rchild.d)||tbf||acc)
    std::string digest;
    // 左右子结点。静态的数组中，使用数组下标作为地址。
    // 对于叶结点，lchild和rchild置-1
    int lchild;
    int rchild;

    // 构造函数
    node(int len_of_bf,int num_of_hashs):tbf(len_of_bf,num_of_hashs)
    {
        lchild=-1;
        rchild=-1;
    }

    /*
        在设置好内部每个字段的值后，计算叶结点的digest
        对于叶结点，digest=H(tbf||acc)
        对于非叶结点，digest=H(H(lchild.d||rchild.d)||tbf||acc)
        使用SHA256作为哈希函数
    */
    void get_leaf_digest(){
        std::string tbf_str=tbf.to_string();
        // tbf||acc
        std::string s=tbf_str+acc;
        int len=s.length();
        char* buf=new char[len];
        Crypto_Primitives::string2char(s,buf);

        char d[SHA256_SIZE];
        int digest_len;
        Crypto_Primitives::SHA256_digest((unsigned char*)buf,len,(unsigned char*)d,(unsigned int*)&digest_len);
        digest=std::string(d,SHA256_SIZE);

        delete[] buf;    
    }


    /*
        在设置好内部每个字段的值后，计算叶结点的digest
        对于叶结点，digest=H(tbf||acc)
        对于非叶结点，digest=H(H(lchild.d||rchild.d)||tbf||acc)
        使用SHA256作为哈希函数

        param:
            ld:左子结点的digest
            rd:右子结点的digest
    */
    void get_nonleaf_digest(std::string ld,std::string rd){
        // H(ld||rd)
        std::string tmp=ld+rd;
        char bytes1[SHA256_SIZE*2];
        Crypto_Primitives::string2char(tmp,bytes1);
        int digest_len;
        char bytes2[SHA256_SIZE];       // 储存H(ld||rd)
        Crypto_Primitives::SHA256_digest((unsigned char*)bytes1,SHA256_SIZE*2,
                            (unsigned char*)bytes2,(unsigned int*)&digest_len);
        
        // tbf||acc
        std::string tmp2=(tbf.to_string())+acc;

        char* buf=new char[SHA256_SIZE+tmp2.length()];
        memcpy(buf,bytes2,SHA256_SIZE);
        Crypto_Primitives::string2char(tmp2,buf+SHA256_SIZE);

        // 求digest
        char ret[SHA256_SIZE];
        Crypto_Primitives::SHA256_digest((unsigned char*)buf,SHA256_SIZE+tmp2.length(),
                                        (unsigned char*)ret,(unsigned int*)&digest_len);
        
        digest=std::string(ret,SHA256_SIZE);

        delete[] buf;
    }
};


 




/*
    merkle树，使用数组储存树（静态形式）
*/
class MerkleTree{
public:
    // 用数组储存树
    std::vector<struct node> tree;

    // 根结点的下标
    int root_id;


    /*
        在tree数组中已经加入了叶结点的前提下，自顶向下的构建一棵平衡的merkle树。
        在这个过程中设置root_id
    */
    void construct_tree();


    // MerkleTree(int len_of_bf,int num_of_hashs);

    MerkleTree(int len_of_bf,int num_of_hashs,MultisetAccumulator msa);


    /*
        根据给定的数据，在merkle树中进行查询

        param:
            x:关键字对应的素数
            locs:BF的k个位置
        return:
            struct query_result
    */
    struct query_result query(std::string& x,std::vector<int>& locs);


    /*
        给定一棵proof_node组成的树，进行merkle proove
        使用递归计算即可

        param:
            query_result: 树
        return:

    */
    static std::string merkle_proove(struct query_result);
    

private:
    /*
        给定一组叶结点，构建一颗子树，将子树的root加入tree并返回在数组中的索引

        param:
            一个队列，储存当前给定的叶结点在tree数组中的下标

        return:
            子树的root_id
    */
    int sub_tree(std::queue<int> leaf_set);

    int len_of_bf;

    int num_of_hashs;

    MultisetAccumulator msa;


    /*
        通过DFS的方式查询关键字，并对所有查询路径上的结点，生成一个proof_node结点加入res数组。
        返回生成的proof_node结点在res数组中的下标

        param:
            id: 当前merkle树结点在tree数组中的下标
            x: 关键字对应的素数
    */
    int DFS_query(int id,std::string& x,std::vector<int>& locs,std::vector<struct proof_node>& res);


    /*
        给定下标为id的结点，计算该结点的digest并储存在结点中

        param:
            id:下标
            res:一个数组，储存树的结点
    */
    static void get_root_hash(int id,std::vector<struct proof_node>& res);
    
};

#endif