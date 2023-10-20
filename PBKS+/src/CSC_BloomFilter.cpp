#include "../include/CSC_BloomFilter.h"
#include "../include/MurmurHash3.h"
#include <algorithm>



CSC_BloomFilter::CSC_BloomFilter(uint8_t num_of_hashs,
    uint16_t num_of_partitions,uint32_t len_of_bf,uint8_t num_of_repetitions) {
    this->num_of_hashs=num_of_hashs;
    this->num_of_partitions=num_of_partitions;
    this->len_of_bf=len_of_bf;
    this->num_of_repetitions=num_of_repetitions;

    // 初始化CSC-BF数组
    for(int i=0;i<this->num_of_repetitions;i++){
        std::vector<bool> v;
        // 设置容量并初始化为false
        v.resize(this->len_of_bf);
        csc_bf.push_back(v);
    }

    // 为CSC-BF的每个位置计算一个随机数gamma并储存
    for(int r=0;r<num_of_repetitions;r++){
        std::vector<std::string> tmp;
        gamma.push_back(tmp);
        for(int i=0;i<len_of_bf;i++){
            gamma[r].push_back(Crypto_Primitives::get_rand(GAMMA_SIZE));
        }
    }    
}


std::vector<int> CSC_BloomFilter::add(std::string w,std::string id){
    // 要返回的映射表
    std::vector<int> v;

    // r：第r个repetition
    for(uint8_t r=0;r<this->num_of_repetitions;r++){
        // 对每个repetition计算g_r(id)
        uint16_t g_r_id=get_g_r_id(r,id);

        // 将g_r(id)加入映射表
        v.push_back(g_r_id);

        // 计算关键字w对各个哈希函数的值，并进行add
        for(int i=0;i<num_of_hashs;i++){
            //h_i(w)
            uint32_t h_i_w=get_h_i_w(i,w);
            csc_bf[r][(h_i_w+g_r_id)%len_of_bf]=true;
        }
    }

    return v;
}


BF_Enc CSC_BloomFilter::SHVE(unsigned char* msk,unsigned char* iv){
    // 创建一个BF_Enc对象
    BF_Enc res;
    res.len_of_bf=this->len_of_bf;
    res.num_of_repetitions=this->num_of_repetitions;

    // 对res的vector引用
    std::vector<std::vector<struct cipher_text>>& vec=res.bf_enc;

    for(int r=0;r<num_of_repetitions;r++){
        // vec分配空间
        vec.push_back(std::vector<struct cipher_text>());
        for(int i=0;i<len_of_bf;i++){
            struct cipher_text tmp;
            vec[r].push_back(tmp);
            // concat BF[i] and i-->BF[i]||i，每个部分16字节（需要填充），连接后为32字节
            // s1，s2分别储存BF[i]和i的字节形式
            std::string s1="";
            s1.resize(CONCAT_SIZE);

            // 若BF[i]==true，对应的字符串中每一位都为1，否则每一位都为0
            bool v=csc_bf[r][i];
            if(v){
                std::fill(s1.begin(),s1.end(),0xFF);
            }
            else{
                std::fill(s1.begin(),s1.end(),0x00);
            }

            // 计算BF_new=BF xnor mask
            char mask_bytes[MASK_SIZE];
            // 计算mask
            get_mask(r,i,(unsigned char*)mask_bytes);
            // 同或
            char xnor_value[MASK_SIZE];    // 储存同或值
            Crypto_Primitives::string_xnor(mask_bytes,(char*)s1.c_str(),MASK_SIZE,xnor_value);

            // 更新s1为BF_new的值
            s1=std::string(xnor_value,CONCAT_SIZE);



            // 将i转换为字符串。若i=16，那么对应的字符串为"0000000000000016"
            std::string s3=std::to_string(i);
            std::string s2="";
            s2.resize(CONCAT_SIZE-s3.length());
            fill(s2.begin(),s2.end(),'0');
            s2.append(s3);


            // 计算d0
            // 计算PRF
            std::string data=s1.append(s2);
            char data_bytes[ALPHA_SIZE];
            Crypto_Primitives::string2char(data,data_bytes);
            char prf_value[ALPHA_SIZE];
            Crypto_Primitives::get_prf(msk,(unsigned char*)data_bytes,data.length(),
            (unsigned char*) prf_value);
            // 生成一个32字节的随机数作为alpha
            std::string alpha=(Crypto_Primitives::get_rand(ALPHA_SIZE));
            char alpha_bytes[ALPHA_SIZE];
            Crypto_Primitives::string2char(alpha,alpha_bytes);
            // 异或
            char xor_value[ALPHA_SIZE];
            Crypto_Primitives::string_xor(prf_value,(char*)alpha_bytes,ALPHA_SIZE,xor_value);
            (vec[r][i]).d0=std::string(xor_value,ALPHA_SIZE);

            // 计算d1
            // 加密的数据为"0000000000000000"
            std::string plain_text="";
            plain_text.resize(PLAINTEXT_SIZE);
            fill(plain_text.begin(),plain_text.end(),'0');
            char cipher_text[PLAINTEXT_SIZE];
            Crypto_Primitives::sym_encrypt((unsigned char*)(plain_text.c_str()),plain_text.length(),
            (unsigned char*)alpha_bytes,iv,(unsigned char*)cipher_text);
            (vec[r][i]).d1=std::string(cipher_text,PLAINTEXT_SIZE);
        }
    }

    return res;
}

int CSC_BloomFilter::get_num_of_repetitions(){
    return num_of_repetitions;
}

int CSC_BloomFilter::get_len_of_bf(){
    return len_of_bf;
}

int CSC_BloomFilter::get_num_of_partitions(){
    return num_of_partitions;
}

int CSC_BloomFilter::get_num_of_hashs(){
    return num_of_hashs;
}

std::array<uint64_t, 2> CSC_BloomFilter::hash(const uint8_t *data, std::size_t len)
{
    std::array<uint64_t, 2> hashValue;
    MurmurHash3_x64_128(data, len, 0, hashValue.data());
    return hashValue;
}

uint64_t CSC_BloomFilter::hash_func(uint8_t n, std::array<uint64_t, 2> hash_array)
{
    uint64_t hash_a = hash_array[0];
    uint64_t hash_b = hash_array[1];
    uint32_t m = this->len_of_bf;
    return (hash_a % m + n * hash_b % m) % m;
}

uint64_t CSC_BloomFilter::partition_func(uint8_t r, std::array<uint64_t, 2> hash_array)
{
    uint64_t hash_a = hash_array[0];
    uint64_t hash_b = hash_array[1];
    uint32_t b = this->num_of_partitions;
    return (r * hash_a % b + hash_b % b) % b;
}



uint16_t CSC_BloomFilter::get_g_r_id(uint8_t r,std::string id){
    const char* id_tmp=id.c_str();
    std::array<uint64_t,2> hash_array=hash((uint8_t*)id_tmp,id.length());
    uint16_t g_r_id=partition_func(r,hash_array);
    return g_r_id;
}


uint32_t CSC_BloomFilter::get_h_i_w(uint8_t i,std::string w){
    const char* w_tmp=w.c_str();
    std::array<uint64_t,2> hash_array=hash((uint8_t*)w_tmp,w.length());
    uint32_t h_i_w=hash_func(i,hash_array);
    return h_i_w;
}



void CSC_BloomFilter::get_mask(int r,int i,unsigned char* mask_data){
    // mask_data初始化


    // 用于对称加密的密钥
    char key[MSK_SIZE]={};

    // gamma值g
    std::string g=gamma[r][i];
    char g_bytes[GAMMA_SIZE];
    Crypto_Primitives::string2char(g,g_bytes);

    // i值转换为字节数组
    char i_bytes[GAMMA_SIZE];
    memset(i_bytes,0,GAMMA_SIZE);
    memcpy(i_bytes+GAMMA_SIZE-sizeof(int),&i,sizeof(int));

    // 使用PRF计算对应mask=PRF(g xor i)
    // 这里的做法是将异或值g xor i作为对称加密的输入，加密结果为mask
    char data[GAMMA_SIZE];
    Crypto_Primitives::string_xor(g_bytes,i_bytes,GAMMA_SIZE,data);
    Crypto_Primitives::get_prf((unsigned char*)key,(unsigned char*)data,GAMMA_SIZE, mask_data);
}