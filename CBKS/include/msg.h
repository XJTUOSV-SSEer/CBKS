#ifndef MSG_H
#define MSG_H

#include "./data_type.h"
#include "BF_Enc.h"

/*
    定义client与server之间通信的数据包
*/


/*
    client发送至server的数据包，用于index_gen
*/
struct build_msg{
    // BF数组的长度
    uint32_t len_of_bf;
    // repetition的数量
    uint8_t num_of_repetitions;
    // 一个二维数组。等价于键为一个pair<int r,int b>，r为repetition的序号，b为分区的序号；值为r中分区值为b的文件id的集合
    std::vector<std::vector<std::set<std::string>>> tab;
    // 加密的CSC-BF
    BF_Enc bf_enc;
    // 对称加密的IV
    std::string iv;
};


/*
    client向server发送的查询请求
*/
struct request_msg{
    // 储存每个可能的基准位置(每个repetition用的哈希函数族一样，对应的h_w也一样)
    std::vector<int> trapdoor;
    // CPRF的token
    unsigned char token[TOKEN_SIZE];
    // 分区数
    int num_of_partitions;
};


/*
    server向client发送的响应
*/
struct respond_msg{
    // 查询结果，一个集合，元素为match的文件id
    std::set<std::string> res;
};


#endif