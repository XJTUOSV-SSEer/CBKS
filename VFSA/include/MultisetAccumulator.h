#ifndef MULTISETACCUMULATOR_H
#define MULTISETACCUMULATOR_H

#include <pbc/pbc.h>


class MultisetAccumulator{
public:
    /*
        构造函数，构造一个双线性对
    */
    MultisetAccumulator();
    

    

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