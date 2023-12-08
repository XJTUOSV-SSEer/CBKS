#include "../include/BigInteger.h"
#include <iostream>


int main(void){
    // 使用较小的正整数构造
    BigInteger x(1281728);
    std::cout<<x.to_string()<<std::endl;
    std::cout<<x.estimate_dec_len()<<std::endl;


    // 构造大整数
    BigInteger a("1381723128379128379137");
    BigInteger b("1943872381928310212938");
    std::cout<<a.estimate_dec_len()<<std::endl;

    // 构造空的大整数
    BigInteger c;

    // 加
    BigInteger::add(c,a,b);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 减
    BigInteger::sub(c,a,b);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 乘
    BigInteger::mul(c,a,b);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 除
    BigInteger d;
    BigInteger::div(c,d,b,a);
    std::cout<<c.to_string()<<" "<<d.to_string()<<std::endl;

    // 平方
    BigInteger::sqr(c,a);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 取模
    BigInteger::mod(c,b,a);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;


    // 幂运算
    BigInteger p(3);
    BigInteger::exp(c,a,p);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 模加
    BigInteger m(1238172832);
    BigInteger::mod_add(c,a,b,m);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 模减
    BigInteger::mod_sub(c,a,b,m);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 模乘
    BigInteger::mod_mul(c,a,b,m);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;

    // 模平方
    BigInteger::mod_sqr(c,a,m);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;


    // 模幂
    p.reset("4");
    BigInteger::mod_exp(c,a,p,m);
    std::cout<<c.to_string()<<std::endl;
    std::cout<<c.estimate_dec_len()<<std::endl;


    // 求逆元
    BigInteger::mod_inverse(c,a,m);
    std::cout<<c.to_string()<<std::endl;

    // 最大公因数
    a.reset(966);
    b.reset(644);
    BigInteger::gcd(c,a,b);
    std::cout<<c.to_string()<<std::endl;


    // 拓展欧几里得算法
    a.reset("13129317293781291298371");
    b.reset("37129387129380129830192");
    BigInteger y;
    BigInteger::xgcd(a,b,x,y);
    std::cout<<x.to_string()<<" "<<y.to_string()<<std::endl;


}