#ifndef MSG_H
#define MSG_H
#include <string>
#include<vector>
#include "MultisetAccumulator.h"

/*
    用户生成的搜索陷门
*/
struct trapdoor{
    // 要查询的关键字对应的素数
    std::string x;
    // k个哈希函数的值loc(理论上还有h_k+1(loc)，但这里省略)
    std::vector<int> locs;
};



/*
    服务器查询时，遍历merkle树，得到多个结点。每个proof_node储存一个结点
*/
struct proof_node{
    // 文件名，只有叶结点填充该字段
    std::string f_id;
    // 记录该结点是否匹配
    bool is_match;
    // 记录该结点是否为叶结点
    bool is_leaf;
    // TBF
    Twin_BloomFilter tbf;
    // acc
    std::string acc;
    // 不相交证明
    struct Nonmembership_Proof pi;
    // 左，右子结点在res数组中的下标
    int lchild;
    int rchild;
    // H(lchild.d||rchild.d)。当结点是不匹配的非叶结点时要填充此字段
    std::string child_digest;
    // digest，初始为空。在merkle证明的过程中计算并填充
    std::string digest;


    /*
        构造函数

        param:
            tbf:merkle树节点中的TBF
    */
    proof_node(const Twin_BloomFilter& tbf):tbf(tbf){

    }


};



/*
    服务器返回的查询结果。即一颗用于merkle proove的树，同时结点中包含了不相交证明等数据
*/
struct query_result{
    // 静态的储存一棵树，即查询得到的结果
    std::vector<struct proof_node> res;
    // 根结点在数组中的下标
    int root_id;
};



#endif