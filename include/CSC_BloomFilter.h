#pragma once

#ifndef CSC_BLOOMFILTER_H
#define CSC_BLOOMFILTER_H

#include "../include/data_type.h"
#include "./BF_Enc.h"
#include "./Crypto_Primitives.h"

class CSC_BloomFilter
{
public:
    /*
        构造函数
        param:
            num_of_hashs
            num_of_partitions
            len_of_bf
            num_of_repetitions
    */
    CSC_BloomFilter(uint8_t num_of_hashs,
    uint16_t num_of_partitions,uint32_t len_of_bf,uint8_t num_of_repetitions);

    /*
        将(w,id) pair加入CSC-BF
        param:
            w：关键字
            id：文件id
        return:
            一个vecotr，映射r->b，即说明id在第r个repetition中的分区为b
    */
    std::vector<int> add(std::string w,std::string id);

    
    /*
        将CSC-BF加密得到BF_Enc
        param:
            msk：主密钥，32字节
            iv：16字节
    */
    BF_Enc SHVE(unsigned char* msk,unsigned char* iv);

    /*
        获取num_of_repetitions
    */
    int get_num_of_repetitions();


    /*
        获取len_of_bf
    */
    int get_len_of_bf();

private:
    // 哈希函数族中哈希函数的数量
    uint8_t num_of_hashs;
    // 分区的数量b
    uint16_t num_of_partitions;
    // BF数组的长度
    uint32_t len_of_bf;
    // repetition的数量
    uint8_t num_of_repetitions;
    // CSC-BF数组
    std::vector<std::vector<bool>> csc_bf;

    /*
        调用Murmurhash3计算data的哈希，返回哈希值
        param:
            data:数据
            len:数据的字节数
        return:
            哈希值，即一个array，包含两个uint64的数据
    */
    std::array<uint64_t, 2> hash(const uint8_t *data, std::size_t len);

    /*
        hash_array包含hash_a和hash_b。通过计算(hash_a+n*hash_b)%len_of_bf得到哈希函数族第n个哈希函数的值
        param:
            n:表示第n个哈希函数
            hash_array:通过hash方法对关键字w处理得到的array
        return:
            第n个哈希函数对于关键字w的哈希值
    */
    uint64_t hash_func(uint8_t n, std::array<uint64_t, 2> hash_array);

    /*
        hash_array包含hash_a和hash_b。通过计算(r*hash_a+hash_b)%num_of_partitions得到第r个repetition的分区函数
        param:
            n:表示第r个repetition
            hash_array:通过hash方法对文件id处理得到的array
        return:
            第r个repetition的分区函数对于文件id的哈希值
    */
    uint64_t partition_func(uint8_t r, std::array<uint64_t, 2> hash_array);


    /*
        计算g_r(id)，即id在第r个repetition中的分区
        param:
            r
            id
        return:
            id在第r个repetition中的分区
    */
    uint16_t get_g_r_id(uint8_t r,std::string id);


    /*
        计算h_i(w)，即第i个哈希函数求出的w的基准位置
    */
    uint32_t get_h_i_w(uint8_t i,std::string w);
};

#endif