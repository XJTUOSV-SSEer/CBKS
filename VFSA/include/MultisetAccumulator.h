#ifndef MULTISETACCUMULATOR_H
#define MULTISETACCUMULATOR_H

#include <pbc/pbc.h>
#include<string>
#include <set>



/*
    储存不相交证明。
*/
struct Disjoint_Proof{
    // pk^Q1
    std::string first;
    // pk^Q2
    std::string second;
};


/*
    RSA累加器
*/
class MultisetAccumulator{
public:
    MultisetAccumulator();



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