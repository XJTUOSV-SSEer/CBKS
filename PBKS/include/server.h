#ifndef SERVER_H
#define SERVER_H
#include "./data_type.h"
#include "BF_Enc.h"
#include "./msg.h"


class server{
public:
    /*
        构造函数。接收用户的build数据包。
    */
    server(struct build_msg m);


    /*
        根据用户的请求，进行搜索，并将匹配的id储存在set中返回
    */
    struct respond_msg search(struct request_msg req);

private:
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



#endif