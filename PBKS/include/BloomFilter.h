#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include "data_type.h"
#include <vector>

class BloomFilter{
    public:
        /* 
            构造函数
            size：BF数组的size
            numHashes：
        */
        BloomFilter(uint64_t size, uint8_t numHashes);

        /*
            data:要插入的数据
            len: data的字节数
        */
        void add(const uint8_t *data, std::size_t len);

        /*
            verify
            len:data的字节数
        */
        bool possiblyContains(const uint8_t *data, std::size_t len) ;
       
    private:
        // 哈希函数族的大小
        uint8_t m_numHashes;
        // BF数组
        std::vector<bool> m_bits;

        /*
            对data调用murmurhash3，返回哈希值（一个std::array）
        */
        std::array<uint64_t, 2> hash(const uint8_t *data,std::size_t len);

        /*
            计算(hashA + n * hashB) % filterSize，等价于一个哈希函数族
        */
        uint64_t nthHash(uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t filterSize);

};
 
#endif