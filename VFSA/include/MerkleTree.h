#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <vector>
#include "Twin_BloomFilter.h"
#include "Crypto_Primitives.h"
#include "data_type.h"

/*
    merkle树的结点
*/
struct node{
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

private:
    /*
        给定一组叶结点，构建一颗子树，将子树的root加入tree并返回在数组中的索引
    */
    int sub_tree(std::set<int> leaf_set);
    
};

#endif