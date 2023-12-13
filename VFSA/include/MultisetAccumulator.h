#ifndef MULTISETACCUMULATOR_H
#define MULTISETACCUMULATOR_H

#include <pbc/pbc.h>
#include<string>
#include <set>


/*
    储存不想交证明。
*/
struct Disjoint_Proof{
    // pk^Q1
    std::string first;
    // pk^Q2
    std::string second;
};

class MultisetAccumulator{
public:
    /*
        构造函数，构造一个双线性对
    */
    MultisetAccumulator();


    /*
        给定关键字集合，计算对应的P(T)
        具体首先将关键字集合转换为素数集合，然后累乘

        param:
            w_set:关键字的集合，关键字为明文形式
        return:
            P(T)的十进制字符串

    */
    std::string get_P(std::set<std::string> w_set);

    /*
        计算acc值
        首先将w_set转换为一个素数集合T，然后计算acc

        param:
            
            w_set:关键字的集合，关键字为明文形式
        return:
            acc: g^P(T)
    */
    std::string Acc(std::set<std::string> w_set);


    /*
        做不相交证明
    */
    struct Disjoint_Proof Prove_Disjoint(std::string PT1,std::string PT2);
    
    

    

private:
    // 双线性对
    pairing_t pairing;
    // 公钥
    element_t public_key;
    // 私钥
    element_t secret_key;
    // 生成元
    element_t g;

};


#endif