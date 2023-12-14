#ifndef MULTISETACCUMULATOR_H
#define MULTISETACCUMULATOR_H

#include <pbc/pbc.h>
#include<string>
#include <set>



/*
    储存不相交证明。
*/
struct Nonmembership_Proof{
    // a
    std::string a;
    // d=g^b mod N
    std::string d;
};


/*
    RSA累加器
*/
class MultisetAccumulator{
public:
    MultisetAccumulator();

    /*
        对于给定的关键字集合，生成ACC

        param:
            w_set: 关键字的明文集合

        return:
            acc的十进制字符串形式
    */
    std::string get_acc(std::set<std::string> w_set);


    /*
        对于给定的关键字集合，计算对应素数的乘积

        param:
            w_set: 关键字的明文集合

        return:
            对应素数的乘积
    */
    std::string get_product(std::set<std::string> w_set);


    /*
        证明某关键字x不存在于某个集合(不存在证明)

        param:
            product:集合对应素数的乘积，十进制字符串形式
            x:关键字的明文
    */
    struct Nonmembership_Proof proove_nonmembership(std::string product,std::string w);


    /*
        给定从服务器获取的acc，不相交证明pi，验证关键字w不属于集合

        param:
            acc:
            pi:
            w:
        return:
            若w不属于集合，返回true。否则返回false
    */
    bool verify_nonmembership(std::string acc,struct Nonmembership_Proof pi,std::string w);



    /*
        使用欧拉降幂公式计算 a^x mod N

        param:
            a,x:十进制字符串
        
        return:
            结果，一个十进制字符串
    */
    std::string mod_exp_Euler(std::string a,std::string x);





private:
    // 安全的素数P
    std::string P;

    // 安全的素数Q
    std::string Q;

    // 模数N=PQ
    std::string N;

    // 生成元g
    unsigned long g;
};


#endif