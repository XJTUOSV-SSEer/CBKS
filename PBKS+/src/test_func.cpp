/* 用于对每个函数进行单元测试 */
#include <iostream>
#include <cstring>
#include "../include/data_type.h"
#include "../include/BloomFilter.h"
#include "../include/CSC_BloomFilter.h"
#include "../include/Crypto_Primitives.h"
#include "../include/client.h"
#include "../include/load_data.h"


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


    // std::set<int> s1,s2,s3;
    // s1.insert(1);
    // s1.insert(2);
    // s2.insert(2);
    // s2.insert(3);
    // std::set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),std::insert_iterator<std::set<int>>(s1,s1.begin()));
    // std::cout<<s1.size()<<std::endl;
    // std::vector<std::string> prfs;
    // prfs.push_back("123");
    // prfs.push_back("456");

    // std::string s1="123456";
    // s1[3]='\0';
    // const char* s=s1.c_str();

    // // std::string s2="456";


    std::string s="";
    s.resize(16);
    std::fill(s.begin(),s.end(),255);

    char ch1=255;
    unsigned char ch2=255;
    return 0;
}
