#ifndef BIGINTEGER_H
#define BIGINTEGER_H


#include <string>
#include <openssl/bn.h>


/*
    大整数类，基于openssl的BIGNUM
*/
class BigInteger{
public:
    /*
        创建空的BIGNUM对象
    */
    BigInteger();

    /*
        使用字符串创建BIGNUM，字符串为数值十进制形式的字面量

        param:
            s:一个字符串，如"21837182"
    */
    BigInteger(std::string s);


    /*
        析构函数，销毁BIGNUM对象
    */
    ~BigInteger();


    /*
        估计整数的位数
    */


private:
    BIGNUM* bi;



};



#endif