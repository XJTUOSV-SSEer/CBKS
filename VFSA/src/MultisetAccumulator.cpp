#include<iostream>
#include "../include/MultisetAccumulator.h"
#include "../include/BigInteger.h"



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


std::string MultisetAccumulator::get_P(std::set<std::string> w_set){
    // 将w_set转换为素数集合T
    std::set<std::string> T;
    for(std::set<std::string>::iterator it=w_set.begin();it!=w_set.end();it++){
        BigInteger n;
        std::string w=(*it);
        BigInteger::generate_prime(n,w);
        T.insert(n.to_string());
    }

    // 求P(T)
    element_t P_T;
    element_init_Zr(P_T,this->pairing);
    element_set1(P_T);      // 初始为1
    for(std::set<std::string>::iterator it=T.begin();it!=T.end();it++){
        std::string s=(*it);
        // 将素数转换为element_t类型
        element_t t;
        element_init_Zr(t,this->pairing);
        element_set_str(t,(char*)s.c_str(),10);

        // 累乘
        // element_mul_zn(P_T,P_T,t);
    }

    char tmp[1024];
    element_snprint(tmp,1024,P_T);

    return std::string(tmp);
}



std::string MultisetAccumulator::Acc(std::set<std::string> w_set){
    // 将w_set转换为素数集合T
    std::set<std::string> T;
    for(std::set<std::string>::iterator it=w_set.begin();it!=w_set.end();it++){
        BigInteger n;
        std::string w=(*it);
        BigInteger::generate_prime(n,w);
        T.insert(n.to_string());
    }

    // 求P(T)
    element_t P_T;
    element_init_Zr(P_T,this->pairing);
    element_set1(P_T);      // 初始为1
    for(std::set<std::string>::iterator it=T.begin();it!=T.end();it++){
        std::string s=(*it);
        // 将素数转换为element_t类型
        element_t t;
        element_init_Zr(t,this->pairing);
        element_set_str(t,(char*)s.c_str(),10);

        // 累乘
        element_mul_zn(P_T,P_T,t);
    }

    // 计算acc=g^P(T)
    element_t acc;
    element_init_G2(acc,this->pairing);
    element_pow_zn(acc,g,P_T);

    // 将acc转换为string返回
    char tmp[1024];
    element_snprint(tmp,1024,acc);
    return std::string(tmp);
}


struct Disjoint_Proof MultisetAccumulator::Prove_Disjoint(std::string PT1,std::string PT2){
    // 将PT1,PT2转换为BigInteger对象
    BigInteger P_T_1(PT1);
    BigInteger P_T_2(PT2);

    // 使用拓展欧几里得定理计算P_T_1*Q1+P_T_2*Q2=1的解
    BigInteger Q1;
    BigInteger Q2;
    BigInteger::xgcd(P_T_1,Q1,P_T_2,Q2);

    // 生成不相交证明
    std::string tmp1=Q1.to_string();
    std::string tmp2=Q2.to_string();
    element_t Q_1,Q_2;
    element_init_Zr(Q_1,this->pairing);
    element_set_str(Q_1,tmp1.c_str(),10);
    element_init_Zr(Q_2,this->pairing);
    element_set_str(Q_2,tmp2.c_str(),10);

    // pk^Q1
    element_t first;
    element_init_G2(first,this->pairing);
    element_pow_zn(first,public_key,Q_1);

    // pk^Q2
    element_t second;
    element_init_G2(second,this->pairing);
    element_pow_zn(second,public_key,Q_2);

    // 构造结果
    char str[1024];
    struct Disjoint_Proof pi;
    element_snprint(str,1024,first);
    pi.first=std::string(str);
    element_snprint(str,1024,second);
    pi.second=std::string(str);

    return pi;
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