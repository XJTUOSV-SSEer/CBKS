#include <string>
#include<iostream>
#include "../include/MultisetAccumulator.h"



MultisetAccumulator::MultisetAccumulator(){
    // 从文件中读取双线性对的参数
    std::string filename = "../src/a.param";
    FILE *fp;
    fp = fopen((char *)filename.c_str(), "r");
    if (!fp)
    {
        pbc_die("error opening %s", filename.c_str());
    }

    char param[1024];
    size_t count = fread(param, 1, 1024, fp);
    if (!count)
        pbc_die("input error");

    // 使用参数初始化双线性对
    pairing_init_set_buf(pairing, param, count);

    // 初始化其他参数
    element_init_G2(g, pairing);
    element_init_G2(public_key, pairing);
    element_init_Zr(secret_key, pairing);

    // 生成g
    element_random(g);
    // 生成私钥
    element_random(secret_key);
    // 计算公钥
    element_pow_zn(public_key,g,secret_key);
}




// int main(void)
// {
//     // 初始化双线性对
//     pairing_t pairing;

//     // 从文件中读取双线性对的参数
//     std::string filename = "../src/a.param";
//     FILE *fp;
//     fp = fopen((char *)filename.c_str(), "r");
//     if (!fp)
//     {
//         pbc_die("error opening %s", filename.c_str());
//     }

//     char param[1024];
//     size_t count = fread(param, 1, 1024, fp);
//     if (!count)
//         pbc_die("input error");

//     // 使用参数初始化双线性对
//     pairing_init_set_buf(pairing, param, count);

//     element_t g;
//     element_t public_key;
//     element_t secret_key;

//     element_init_G2(g, pairing);
//     element_init_G2(public_key, pairing);
//     element_init_Zr(secret_key, pairing);

//     // 生成g
//     element_random(g);
//     // 生成私钥
//     element_random(secret_key);
//     // 计算公钥
//     element_pow_zn(public_key,g,secret_key);


//     // 生成x,y
//     element_t x,y;
//     element_init_Zr(x,pairing);
//     element_random(x);
//     element_init_Zr(y,pairing);
//     element_random(y);

//     // 生成a,b
//     element_t a,b;
//     element_init_G1(a,pairing);
//     element_random(a);
//     element_init_G2(b,pairing);
//     element_random(b);

//     // a^x,b^y
//     element_t tmp1;
//     element_init_G1(tmp1,pairing);
//     // _zn表示是在循环群上的幂运算
//     element_pow_zn(tmp1,a,x);
//     element_t tmp2;
//     element_init_G2(tmp2,pairing);
//     element_pow_zn(tmp2,b,y);

//     // 计算e(a^x,b^y)
//     element_t res1;
//     element_init_GT(res1,pairing);
//     pairing_apply(res1,tmp1,tmp2,pairing);

//     // 计算e(a,b)^xy
//     element_t tmp3,tmp4;
//     element_init_GT(tmp3,pairing);
//     element_init_Zr(tmp4,pairing);
//     pairing_apply(tmp3,a,b,pairing);
//     element_mul_zn(tmp4,x,y);

//     element_t res2;
//     element_init_GT(res2,pairing);
//     element_pow_zn(res2,tmp3,tmp4);

//     // 比较两个结果
//     if(0==element_cmp(res1,res2)){
//         std::cout<<"equal"<<std::endl;
//     }

//     // 输出参数
//     char s[1024];

//     element_snprint(s,1024,res1);
//     std::cout<<std::string(s)<<std::endl;

//     element_printf("%B\n", res2);
    
//     return 0;
// }