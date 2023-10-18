/* 用于对每个函数进行单元测试 */
#include <iostream>
#include <cstring>
#include "../include/data_type.h"
#include "../include/BloomFilter.h"
#include "../include/CSC_BloomFilter.h"
#include "../include/Crypto_Primitives.h"
#include "../include/client.h"
#include "../include/load_data.h"
#include "../include/CPRF.h"


bool test_BloomFilter()
{
    // 创建一个BF
    BloomFilter *bf = new BloomFilter(1000, 3);

    // add
    for (int i = 0; i < 100; i++)
    {
        byte d[4];
        int a = i;
        memcpy(d, &a, sizeof(int));
        bf->add((uint8_t *)d, sizeof(int));
    }

    // query
    for(int i=0;i<100;i++){
        byte d[4];
        int a = i;
        memcpy(d, &a, sizeof(int));
        bool res=bf->possiblyContains((uint8_t*)d,sizeof(int));
        std::cout<<"i:"<<res<<std::endl;
    }

    // invalid element
    for(int i=101;i<200;i++){
        byte d[4];
        int a = i;
        memcpy(d, &a, sizeof(int));
        bool res=bf->possiblyContains((uint8_t*)d,sizeof(int));
        std::cout<<"i:"<<i<<" "<<res<<std::endl;
    }
}



bool test_CSC_BF(){
    CSC_BloomFilter bf=CSC_BloomFilter(5,100,100,5);
    bf.add(std::string("w1"),std::string("f1"));
    return true;
}


void test_Enc_Dec(){
    std::string p="i am zhaohongguang";
    std::string key="XJTU-OSV-KEY";
    std::string iv="XJTU-OSV-IV";
    // key填充到32字节（仅为示例，将0填充在了后面，实际是不合理的）
    key.resize(32);
    // iv填充到16字节
    iv.resize(16);
    // 预留空间储存密文和解密结果
    char cipher[32];
    char res[32];

    // 加密
    int ciphertext_len=Crypto_Primitives::sym_encrypt((unsigned char*)(p.c_str()),p.length(),
    (unsigned char*)(key.c_str()), (unsigned char*)iv.c_str(),(unsigned char*)cipher);

    // 解密
    int plaintext_len=Crypto_Primitives::sym_decrypt((unsigned char*)cipher,ciphertext_len,
    (unsigned char*)(key.c_str()),(unsigned char*)iv.c_str(),(unsigned char*)res);
    res[plaintext_len]='\0';
    std::cout<<res<<std::endl;
}


void test_get_rand(){
    std::string s=Crypto_Primitives::get_rand(20);
    std::cout<<s<<std::endl;
}


void test_get_prf(){
    std::string key="XJTU-OSV-KEY";
    std::string data="i am zhaohongguang";
    char v[32];

    Crypto_Primitives::get_prf((unsigned char*)(key.c_str()),(unsigned char*)(data.c_str()),data.length(),(unsigned char*)v);
}


void test_string_xor(){
    std::string a="01";
    std::string b="ab";
    char res[2];
    Crypto_Primitives::string_xor((char*)a.c_str(),(char*)b.c_str(),a.length(),res);
    std::cout<<res[0]<<res[1]<<std::endl;
}


void test_SHA512(){
    char digest[64]={};
    
    int digest_len=0;
    std::string a="01";
    Crypto_Primitives::SHA512_digest((unsigned char*)a.c_str(),a.length(),(unsigned char*)digest,(unsigned int*)&digest_len);
    std::cout<<digest_len<<std::endl;
    std::cout<<std::string(digest,digest_len)<<std::endl;
}



void test_CPRF(){
    std::string K="";
    K.resize(MSK_SIZE);
    std::string data="zhg123";
    // std::string data="12";
    char data_bytes[8];
    memcpy(data_bytes,data.c_str(),data.length());
    // 直接计算
    char v1[PRF_SIZE];
    CPRF::prf(K,(unsigned char*)data_bytes,data.length(),(unsigned char*)v1);

    // 先计算token再计算
    char v2[PRF_SIZE];
    unsigned char token[PRF_SIZE];
    unsigned char prefix[8];
    memcpy(prefix,data.c_str(),3);
    CPRF::get_token(K,prefix,3,token);

    unsigned char suffix[8];
    memcpy(suffix,std::string("123").c_str(),3);
    CPRF::eval(std::string((char*)token,TOKEN_SIZE),suffix,3,(unsigned char*)v2);

    // 比较v1和v2
    if(std::string(v1,PRF_SIZE)==std::string(v2,PRF_SIZE)){
        std::cout<<"correct"<<std::endl;
    }
    else{
        std::cout<<"wrong"<<std::endl;
    }

    // char p1[1];
    // char p2[1];
    // p1[0]='0';
    // p1[0]='1';
    // unsigned char t1[TOKEN_SIZE];
    // unsigned char t2[TOKEN_SIZE];
    // CPRF::get_token(K,(unsigned char*)p1,1,t1);
    // CPRF::get_token(K,(unsigned char*)p2,1,t2);

    // if(std::string((char*)t1,TOKEN_SIZE)==std::string((char*)t2,TOKEN_SIZE)){
    //     std::cout<<"error"<<std::endl;
    // }

    char str1[17]={};
    str1[0]='0';
    str1[16]='7';
    char str2[17]={};
    str2[0]='1';
    str2[16]='7';
    char tmp1[32];
    char tmp2[32];

    CPRF::get_token(K,(unsigned char*)str1,1,token);
    CPRF::eval(std::string((char*)token,TOKEN_SIZE),(unsigned char*)(str2+1),16,(unsigned char*)tmp1);
    CPRF::prf(K,(unsigned char*)str2,17,(unsigned char*)tmp2);
}

int main(void)
{
    // 测试布隆过滤器
    // test_BloomFilter();

    // 测试CSC-BF
    // test_CSC_BF();

    // 测试aes加密
    // test_Enc_Dec();

    // 测试随机数生成
    // test_get_rand();

    // 测试PRF
    // test_get_prf();

    // 测试字符串xor
    // test_string_xor();


    // test_SHA512();

    test_CPRF();

    return 0;
}
