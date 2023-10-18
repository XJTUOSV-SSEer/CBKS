#include "../include/CPRF.h"


void CPRF::prf(std::string K,unsigned char* data,int len,unsigned char* v){
    // 记录计算过程中当前得到的PRG值
    unsigned char PRG[PRF_SIZE*2];
    unsigned int PRG_len=0;
    // 记录计算过程中当前结点对应的数据，初始化为K
    unsigned char leaf_value[PRF_SIZE];
    Crypto_Primitives::string2char(K,(char*)leaf_value);

    // 对data的每一位都进行判断0/1，然后获取下一个结点的值
    // 从高位开始
    for(int i=0;i<len;i++){
        // 按字节进行
        unsigned char ch=data[i];
        // 字节内按位处理
        for(int j=7;j>=0;j--){
            // 计算PRG值
            Crypto_Primitives::SHA512_digest(leaf_value,PRF_SIZE,PRG,&PRG_len);

            // 位为0，注意与运算的两个数应长度相同，都为一个字节
            char c=1;
            c=c<<j;
            if((c & ch) == 0){
                memcpy(leaf_value,PRG,PRF_SIZE);
            }
            // 位为1
            else{
                memcpy(leaf_value,PRG+PRF_SIZE,PRF_SIZE);                
            }            
        }
    }

    memcpy(v,leaf_value,PRF_SIZE);
}


void CPRF::get_token(std::string K,unsigned char* prefix,int len,unsigned char* v){
    prf(K,prefix,len,v);
}



void CPRF::eval(std::string token,unsigned char* suffix,int len,unsigned char* v){
    prf(token,suffix,len,v);
}