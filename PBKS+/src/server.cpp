#include "../include/server.h"
#include "../include/Crypto_Primitives.h"


server::server(struct build_msg m){
    this->bf_enc=m.bf_enc;
    this->len_of_bf=m.len_of_bf;
    this->num_of_repetitions=m.num_of_repetitions;
    this->tab=m.tab;
    this->iv=m.iv;
}


struct respond_msg server::search(struct request_msg req){
    std::vector<std::vector<std::pair<int,std::vector<std::string>>>>& trapdoor=req.trapdoor;


    char iv_bytes[IV_SIZE];
    Crypto_Primitives::string2char(iv,iv_bytes);
    

    // result储存最终的查询结果
    std::set<std::string> result;
    for(int r=0;r<num_of_repetitions;r++){
        // 每个repetition维护一个set，储存match的分区号
        // 由于同一个repetition的分区函数相同，所以在每个哈希函数的处理中也维护一个set，储存match的分区号
        // 最后各个哈希函数对应的set相交，得到repetition的分区号
        std::set<int> set_repetition;

        // 每个哈希函数
        for(int k=0;k<(trapdoor[r]).size();k++){
            std::pair<int,std::vector<std::string>> p=trapdoor[r][k];
            int h_w=p.first;
            std::vector<std::string> prfs_value=p.second;

            // 当前哈希函数对应的set
            std::set<int> set_hash;

            // 每个分区
            for(int i=0;i<prfs_value.size();i++){
                // 密文
                struct cipher_text ct=(bf_enc.bf_enc)[r][(h_w+i)%len_of_bf];
                // 计算alpha=PRF xor d0
                char alpha[ALPHA_SIZE];
                char d0_bytes[ALPHA_SIZE];
                Crypto_Primitives::string2char(ct.d0,d0_bytes);
                char prfs_bytes[ALPHA_SIZE];
                Crypto_Primitives::string2char(prfs_value[i],prfs_bytes);
                Crypto_Primitives::string_xor((char*)d0_bytes,(char*)prfs_bytes,ALPHA_SIZE,alpha);
                // 使用alpha解密，判断结果是否为"0000000000000000"
                char plain_text[PLAINTEXT_SIZE];
                char d1_bytes[PLAINTEXT_SIZE];
                Crypto_Primitives::string2char(ct.d1,d1_bytes);

                Crypto_Primitives::sym_decrypt((unsigned char*)d1_bytes,PLAINTEXT_SIZE,(unsigned char*) alpha,
                (unsigned char*)iv_bytes,(unsigned char*)plain_text);
                std::string zero_str="";    // 全0
                zero_str.resize(PLAINTEXT_SIZE);
                fill(zero_str.begin(),zero_str.end(),'0');
                if(std::string(plain_text,PLAINTEXT_SIZE)==zero_str){
                    // 将分区i加入
                    set_hash.insert(i);
                }
            }

            // 特判，第一个哈希函数
            if(k==0){
                set_repetition=set_hash;
            }
            else{
                // 求交集
                std::set<int> tmp;
                std::set_intersection(set_hash.begin(),set_hash.end(),set_repetition.begin(),set_repetition.end()
                ,std::insert_iterator<std::set<int>>(tmp,tmp.begin()));
                set_repetition=tmp;
            }

        
        }

        // 将set_repetition对应的分区解析为id
        std::set<std::string> ids;      // 该repetition对应的id
        for(std::set<int>::iterator it=set_repetition.begin();it!=set_repetition.end();it++){
            int b=*it;
            // 解析
            std::set<std::string> tmp_set=tab[r][b];
            // 将id加入ids
            ids.insert(tmp_set.begin(),tmp_set.end());
        }

        // 将ids与result做交集
        if(r==0){
            // 特判
            result=ids;
        }
        else{
            // 交集
            std::set<std::string> tmp;
            std::set_intersection(ids.begin(),ids.end(),result.begin(),result.end(),
            std::insert_iterator<std::set<std::string>>(tmp,tmp.begin()));
            result=tmp;
        }
    }

    struct respond_msg m;
    m.res=result;
    return m;
}