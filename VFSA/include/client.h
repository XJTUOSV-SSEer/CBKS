#ifndef CLIENT_H
#define CLIENT_H

#include <set>
#include <string>
#include <vector>
#include "../include/MerkleTree.h"
#include "msg.h"
/*
    client类
*/
class client{
public:
    /*
        初始化对象。
        param:
            num_of_hashs:
            len_of_bf:
            
    */
    client(int num_of_hashs,int len_of_bf);


    /*
        生成索引
        将多个文件的内容转换为TBF，然后组织成一棵Merkle树

        param:
            dataset: 数据集。vector中每个元素是一个pair，pair第一个成员为文件名，第二个成员为一个set储存文件中所有关键字
        return:
            一颗merkle树
    */
    MerkleTree index_gen(std::vector<std::pair<std::string,std::set<std::string>>> dataset);


    /*
        给定关键字w，计算对应的搜索陷门

        param:
            w: 要搜索的关键字
        return:
            搜索陷门结构体
    */
    struct trapdoor trap_gen(std::string w);



    /*
        验证结果
        首先进行merkle proove，验证数据的完整性
        然后遍历所有结点。对匹配的叶结点，检查TBF判断是否包含关键字；对不匹配的结点，验证不存在性
    */
    void verify_result(std::string w,struct query_result qr);


private:
    // TBF中哈希函数的数量
    int num_of_hashs;
    // TBF的长度
    int len_of_bf;
    // 累加器
    MultisetAccumulator msa;
    // merkle树的根哈希
    std::string root_hash;
};


#endif