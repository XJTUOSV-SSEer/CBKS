#ifndef TWIN_BLOOMFILTER_H
#define TWIN_BLOOMFILTER_H

#include <vector>
#include <array>

class Twin_BloomFilter{
public:
    /*
        构造函数
        param:
            BF长度
    */
    Twin_BloomFilter(int len_of_bf,int num_of_hashs);


    /*
        给定数据，计算第i个哈希函数族第n个哈希函数的值（已对len_of_bf取过模）

        param:

    */
    uint64_t get_h_i(std::string w,int i);


    /*
        叶结点的bf的add操作

        param:
            w: 关键字

    */
    void add(std::string w);

    /*
        非叶结点的bf的merge操作。将左右子结点的TBF融合

        param:
            lchild,rchild：左、右子结点中的TBF
    */
    void merge(Twin_BloomFilter& lchild,Twin_BloomFilter& rchild);


    /*
        给定位置，计算该位置被选中的cell是0还是1
        公式：H(h_k+1(loc) xor gamma)

        param:
            loc: 位置在数组中的下标
    */
    int get_chosen_cell(int loc);

    /*
        给定h_k+1(loc)，计算对应的chosen cell。该方法主要由CSP调用

        param:
            digest:使用SHA256计算得到的h_k+1(loc)
            loc: 位置的下标
        return:
            该位置的chosen cell
    */
    int get_chosen_cell(char* digest,int loc);


    /*
        获取第loc个位置，chosen_cell处的值
    */
    bool get_value(int loc,int chosen_cell);


    /*
        将twin_BF数组转换为01字符串，用于计算哈希
    */
    std::string to_string();
    

private:
    // BF数组的长度
    int len_of_bf;
    // twin_BF数组
    std::vector<bool> twin_bf[2];
    // gamma数组，储存BF数组每个位置上的随机数gamma
    std::vector<std::string> gamma_vec;

    // 哈希函数数量
    int num_of_hashs;

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



    

};





#endif