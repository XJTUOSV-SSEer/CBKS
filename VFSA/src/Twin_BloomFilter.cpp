#include "../include/Twin_BloomFilter.h"
#include "../include/MurmurHash3.h"
#include "../include/data_type.h"
#include "../include/Crypto_Primitives.h"

Twin_BloomFilter::Twin_BloomFilter(int len_of_bf,int num_of_hashs){
    // 为布隆过滤器分配空间
    for(int i=0;i<2;i++){
        twin_bf[i].resize(len_of_bf);
    }

    // 随机生成gamma数组
    for(int i=0;i<len_of_bf;i++){
        // 生成随机数gamma
        std::string gamma=Crypto_Primitives::get_rand(GAMMA_SIZE);
        gamma_vec.push_back(gamma);
    }

    // 对TBF每一位的chosen cell置0，非chosen cell置1
    for(int i=0;i<len_of_bf;i++){
        int chosen_cell=get_chosen_cell(i);
        twin_bf[chosen_cell][i]=false;
        twin_bf[1-chosen_cell][i]=true;
    }
    
    this->len_of_bf=len_of_bf;
    this->num_of_hashs=num_of_hashs;
}


std::array<uint64_t, 2> Twin_BloomFilter::hash(const uint8_t *data, std::size_t len)
{
    std::array<uint64_t, 2> hashValue;
    MurmurHash3_x64_128(data, len, 0, hashValue.data());
    return hashValue;
}


uint64_t Twin_BloomFilter::hash_func(uint8_t n, std::array<uint64_t, 2> hash_array)
{
    uint64_t hash_a = hash_array[0];
    uint64_t hash_b = hash_array[1];
    uint32_t m = this->len_of_bf;
    return (hash_a % m + n * hash_b % m) % m;
}



int Twin_BloomFilter::get_chosen_cell(int loc){
    // 计算h_k+1(loc)，使用SHA256
    char digest[SHA256_SIZE];
    int digest_len;
    Crypto_Primitives::SHA256_digest((unsigned char*)(&loc),sizeof(int),(unsigned char*)digest,
                                        (unsigned int*)&digest_len);

    // h_k+1 xor gamma
    char gamma_bytes[GAMMA_SIZE];
    Crypto_Primitives::string2char(gamma_vec[loc],gamma_bytes);
    char res_bytes[GAMMA_SIZE];
    Crypto_Primitives::string_xor(digest,gamma_bytes,GAMMA_SIZE,res_bytes);

    // 求哈希H()，使用SHA256
    char c[SHA256_SIZE];
    Crypto_Primitives::SHA256_digest((unsigned char*)res_bytes,GAMMA_SIZE,(unsigned char*)c,
                                        (unsigned int*)&digest_len);
    
    // 若H()的值是奇数，chosen cell为1；否则为0
    // 具体只需要判断最后一位
    unsigned int num=c[SHA256_SIZE-1];
    return num%2;
}


uint64_t Twin_BloomFilter::get_h_i(std::string w,int i){
    std::array<uint64_t,2> hash_array=hash((uint8_t*)(w.c_str()),w.length());
    uint64_t h_i_w=hash_func(i,hash_array);
    return h_i_w;
}



void Twin_BloomFilter::add(std::string w)
{
    // 对k个哈希函数，分别计算值。
    for(int i=0;i<num_of_hashs;i++){
        // 位置
        int loc=get_h_i(w,i);
        // 计算chosen cell
        int chosen_cell=get_chosen_cell(loc);
        // 置位
        twin_bf[chosen_cell][loc]=true;
        twin_bf[1-chosen_cell][loc]=false;
    }
}


void Twin_BloomFilter::merge(Twin_BloomFilter& lchild,Twin_BloomFilter& rchild){
    // 对每个位置都进行处理
    for(int i=0;i<len_of_bf;i++){
        // 计算左、右子结点的chosen cell
        int chosen_cell_left;
        int chosen_cell_right;

        chosen_cell_left=lchild.get_chosen_cell(i);
        chosen_cell_right=rchild.get_chosen_cell(i);

        // 获取左、右子结点在该位的真实值
        bool l_v = lchild.twin_bf[chosen_cell_left][i];
        bool r_v = rchild.twin_bf[chosen_cell_right][i];

        // 计算当前TBF在该位置的值v = l_v or r_v
        bool v = l_v || r_v;

        // 计算当前TBF在该位的chosen cell
        int chosen_cell=get_chosen_cell(i);
        twin_bf[chosen_cell][i]=v;
        twin_bf[1-chosen_cell][i]=(!v);
    }
}


int Twin_BloomFilter::get_chosen_cell(char* digest, int loc){
    // h_k+1 xor gamma
    char gamma_bytes[GAMMA_SIZE];
    Crypto_Primitives::string2char(gamma_vec[loc],gamma_bytes);
    char res_bytes[GAMMA_SIZE];
    Crypto_Primitives::string_xor(digest,gamma_bytes,GAMMA_SIZE,res_bytes);

    // 求哈希H()，使用SHA256
    char c[SHA256_SIZE];
    int digest_len;
    Crypto_Primitives::SHA256_digest((unsigned char*)res_bytes,GAMMA_SIZE,(unsigned char*)c,
                                        (unsigned int*)&digest_len);
    
    // 若H()的值是奇数，chosen cell为1；否则为0
    // 具体只需要判断最后一位
    unsigned int num=c[SHA256_SIZE-1];
    return num%2;
}


bool Twin_BloomFilter::get_value(int loc,int chosen_cell){
    return twin_bf[chosen_cell][loc];
}


std::string Twin_BloomFilter::to_string(){
    std::string ret="";
    for(int i=0;i<len_of_bf;i++){
        for(int j=0;j<2;j++){
            std::string s=std::to_string(twin_bf[j][i]);
            ret.append(s);
        }
    }

    return ret;
}



bool Twin_BloomFilter::verify(std::string w){
    for(int i=0;i<num_of_hashs;i++){
        // 计算w的位置loc和chosen cell
        int loc=get_h_i(w,i);
        int cell=get_chosen_cell(loc);
        bool value=get_value(loc,cell);
        if(!value){
            return false;
        }
    }

    return true;
}