#ifndef BF_ENC_H
#define BF_ENC_H
#include "../include/data_type.h"

/**/
struct cipher_text
{
    // 256位
    std::string d0;
    // 128位
    std::string d1;

    // // 构造函数，为d0和d1分配空间
    // cipher_text(){
    //     d0.resize(ALPHA_SIZE);
    //     d1.resize(PLAINTEXT_SIZE);
    // }
};

class BF_Enc
{
public:
    // BF数组的长度
    uint32_t len_of_bf;
    // repetition的数量
    uint8_t num_of_repetitions;
    // BF_Enc数组
    std::vector<std::vector<struct cipher_text>> bf_enc;

    /*
        
    */
};

#endif