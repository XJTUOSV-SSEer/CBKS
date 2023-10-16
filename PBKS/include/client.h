#ifndef CLIENT_H
#define CLIENT_H
#include "./CSC_BloomFilter.h"
#include "./data_type.h"
#include "./msg.h"


class client{
public:
    /*
        生成一个主密钥，一个IV， 
    */
    client(uint8_t num_of_hashs,
    uint16_t num_of_partitions,uint32_t len_of_bf,uint8_t num_of_repetitions);

    /*
        插入数据

        param:
            inverted_index：倒排索引。一个集合，集合中元素为pair，即w-id
        return:
            一个二维数组。等价于键为一个pair<int r,int b>，r为repetition的序号，b为分区的序号；
            值为r中分区值为b的文件id的集合
    */
    struct build_msg build(std::set<std::pair<std::string,std::string>> inverted_index);    

 
    /*
        search，根据关键字计算得到对应的查询请求
    */
    struct request_msg search(std::string w);

private:
    // 一个CSC-BF对象
    CSC_BloomFilter bf;
    // 主密钥，32字节
    std::string msk;
    // 对称加密的iv
    std::string iv;


    
};



#endif