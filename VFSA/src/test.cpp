#include "../include/BigInteger.h"
// #include "../include/Twin_BloomFilter.h"
// #include "../include/MultisetAccumulator.h"
#include <iostream>
#include <pbc/pbc.h>




// int main(void){
//     MultisetAccumulator msa;
//     std::set<std::string> w_set1;
//     std::set<std::string> w_set2;
//     w_set1.insert("z");
//     w_set1.insert("h");
//     w_set2.insert("j");
//     w_set2.insert("y");



//     // std::cout<<msa.get_P(w_set1)<<std::endl;
//     // std::cout<<msa.get_P(w_set2)<<std::endl;

//     std::string PT1=msa.get_P(w_set1);
//     std::string PT2=msa.get_P(w_set2);

//     BigInteger a(PT1);
//     BigInteger b(PT2);

//     std::cout<<BigInteger::is_prime(a)<<" "<<BigInteger::is_prime(b)<<std::endl;

//     struct Disjoint_Proof pi=msa.Prove_Disjoint(PT1,PT2);
//     std::cout<<pi.first<<std::endl;
//     std::cout<<pi.second<<std::endl;
// }


// int main(void){
//     MultisetAccumulator msa;
//     std::set<std::string> w_set;
//     w_set.insert("z");
//     w_set.insert("h");
//     w_set.insert("g");
//     for(int i=0;i<10;i++){
//         std::string acc=msa.Acc(w_set);
//         std::cout<<acc<<std::endl;
//     }    
// }


// int main(void){
//     std::cout<<"hello"<<std::endl;
// }

int main(void){
    std::string s="zhg";
    BigInteger n;
    BigInteger::generate_prime(n,s);

    std::cout<<n.to_string()<<std::endl;
    std::cout<<BigInteger::is_prime(n)<<std::endl;
    std::cout<<n.estimate_dec_len()<<std::endl;

    return 0;
}


// int main(void){
//     Twin_BloomFilter tbf1(10,2);
//     Twin_BloomFilter tbf2(10,2);
//     Twin_BloomFilter tbf3(10,2);

//     // for(int i=0;i<10;i++){
//     //     std::cout<<tbf1.get_h_i("z",i)<<std::endl;
//     // }

//     tbf1.add("z");
//     tbf3.merge(tbf1,tbf2);

//     return 0;
// }


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
//     element_printf("g:%B\n",g);
//     // 生成私钥
//     element_random(secret_key);
//     element_printf("sk:%B\n",secret_key);
//     // 计算公钥
//     element_pow_zn(public_key,g,secret_key);
//     element_printf("pk:%B\n",public_key);


//     // 生成x,y
//     element_t x,y;
//     element_init_Zr(x,pairing);
//     element_random(x);
//     element_init_Zr(y,pairing);
//     element_random(y);
//     element_printf("x:%B\n",x);
//     element_printf("y:%B\n",y);

//     // 生成a,b
//     element_t a,b;
//     element_init_G1(a,pairing);
//     element_random(a);
//     element_init_G2(b,pairing);
//     element_random(b);
//     element_printf("a:%B\n",a);
//     element_printf("b:%B\n",b);

//     // a^x,b^y
//     element_t tmp1;
//     element_init_G1(tmp1,pairing);
//     // _zn表示是在循环群上的幂运算
//     element_pow_zn(tmp1,a,x);
//     element_t tmp2;
//     element_init_G2(tmp2,pairing);
//     element_pow_zn(tmp2,b,y);

//     element_printf("a^x:%B\n",tmp1);
//     element_printf("b^y:%B\n",tmp2);

//     // 计算e(a^x,b^y)
//     element_t res1;
//     element_init_GT(res1,pairing);
//     pairing_apply(res1,tmp1,tmp2,pairing);
//     element_printf("e(a^x,b^y):%B\n",res1);

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

//     element_snprint(s,1024,public_key);
//     std::cout<<std::string(s)<<std::endl;

//     element_printf("%B\n", res2);


//     // 字符串转element_t
//     element_t tmp5;
//     element_init_GT(tmp5,pairing);
//     element_set_str(tmp5,s,10);
//     element_printf("%B\n", tmp5);

//     return 0;
// }





// int main(void){
//     BigInteger n;

//     // 使用较小的正整数构造
//     BigInteger x(1281728);
//     std::cout<<x.to_string()<<std::endl;
//     std::cout<<x.estimate_dec_len()<<std::endl;


//     // 构造大整数
//     BigInteger a("1381723128379128379137");
//     BigInteger b("1943872381928310212938");
//     std::cout<<a.estimate_dec_len()<<std::endl;

//     // 构造空的大整数
//     BigInteger c;

//     // 加
//     BigInteger::add(c,a,b);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 减
//     BigInteger::sub(c,a,b);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 乘
//     BigInteger::mul(c,a,b);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 除
//     BigInteger d;
//     BigInteger::div(c,d,b,a);
//     std::cout<<c.to_string()<<" "<<d.to_string()<<std::endl;

//     // 平方
//     BigInteger::sqr(c,a);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 取模
//     BigInteger::mod(c,b,a);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;


//     // 幂运算
//     BigInteger p(3);
//     BigInteger::exp(c,a,p);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 模加
//     BigInteger m(1238172832);
//     BigInteger::mod_add(c,a,b,m);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 模减
//     BigInteger::mod_sub(c,a,b,m);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 模乘
//     BigInteger::mod_mul(c,a,b,m);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;

//     // 模平方
//     BigInteger::mod_sqr(c,a,m);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;


//     // 模幂
//     p.reset("4");
//     BigInteger::mod_exp(c,a,p,m);
//     std::cout<<c.to_string()<<std::endl;
//     std::cout<<c.estimate_dec_len()<<std::endl;


//     // 求逆元
//     BigInteger::mod_inverse(c,a,m);
//     std::cout<<"inv_a:"<<c.to_string()<<std::endl;

//     // 最大公因数
//     a.reset(966);
//     b.reset(644);
//     BigInteger::gcd(c,a,b);
//     std::cout<<c.to_string()<<std::endl;


//     // 拓展欧几里得算法
//     a.reset("13129317293781291298371");
//     b.reset("37129387129380129830192");
//     BigInteger y;
//     BigInteger::xgcd(a,b,x,y);
//     std::cout<<x.to_string()<<" "<<y.to_string()<<std::endl;


//     // 生成素数
//     BigInteger::generate_prime(c,256,1);
//     std::cout<<c.to_string()<<std::endl;


//     // 素性测试
//     std::cout<<BigInteger::is_prime(c)<<std::endl;


//     // 模幂，幂为负数
//     a.reset("1381723128379128379137");
//     b.reset("1943872381928310212938");

//     p.reset("-20");
//     BigInteger::mod_exp(c,a,p,m);
//     std::cout<<c.to_string()<<std::endl;
// }


// int main(void){
//     BigInteger n;
//     std::cout<<sizeof(n)<<std::endl;
//     std::cout<<n.to_string()<<std::endl;

//     BigInteger m("1");
//     std::cout<<m.to_string()<<std::endl;


//     return 0;
// }