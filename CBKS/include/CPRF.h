#ifndef CPRF_H
#define CPRF_H
#include "./data_type.h"
#include "./Crypto_Primitives.h"


class CPRF{
public:
    /*
        直接计算data的GGM_PRF

        param:
            K：密钥
            data：数据
            len：数据的长度
            v：储存GGM_PRF值，需要预先分配空间
    */
    static void prf(std::string K,unsigned char* data,int len,unsigned char* v);


    /*
        根据K和前缀计算token
        param:
            K：密钥
            prefix：前缀
            len：前缀的长度
            token：储存token值，需要预先分配空间
    */
    static void get_token(std::string K,unsigned char* prefix,int len,unsigned char* token);

    /*
        根据token和后缀suffix，计算PRF(K,prefix||suffix) = PRF(token,suffix)
    */
    static void eval(std::string token,unsigned char* suffix,int len,unsigned char* v);
};


#endif