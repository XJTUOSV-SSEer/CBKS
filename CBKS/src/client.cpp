#include "../include/client.h"
#include "../include/Crypto_Primitives.h"
#include "../include/CPRF.h"

client::client(uint8_t num_of_hashs,
               uint16_t num_of_partitions,
               uint32_t len_of_bf,
               uint8_t num_of_repetitions) : bf(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions)
{
    // refresh计数器
    refresh_cnt=0;

    // 随机生成主密钥
    msk="XJTU-OSV-MSK00000000000000000000";
    // msk = Crypto_Primitives::get_rand(MSK_SIZE);

    // 固定的IV
    iv="XJTU-OSV-IV12345";
    // iv = Crypto_Primitives::get_rand(IV_SIZE);
}

struct build_msg client::build(std::set<std::pair<std::string, std::string>> inverted_index)
{
    // 创建哈希表（后续发送至服务器）
    std::vector<std::vector<std::set<std::string>>> tab;
    // 预留空间
    for(int i=0;i<bf.get_num_of_repetitions();i++){
        std::vector<std::set<std::string>> tmp;
        tmp.resize(bf.get_num_of_partitions());
        tab.push_back(tmp);
    }

    // 遍历倒排索引进行处理
    for(std::set<std::pair<std::string,std::string>>::iterator it=inverted_index.begin();it!=inverted_index.end();it++){
        // 获取w和id
        std::string w=it->first;
        std::string id=it->second;
        // 插入CSC-BF
        std::vector<int> v=bf.add(w,id,refresh_cnt);

        // 更新哈希表
        for(int r=0;r<v.size();r++){
            int b=v[r];
            // 将id加入tab[r][b]对应的集合
            (tab[r][b]).insert(id);
        }

    }


    // 加密CSC-BF
    char msk_bytes[MSK_SIZE];
    Crypto_Primitives::string2char(msk,msk_bytes);
    char iv_bytes[IV_SIZE];
    Crypto_Primitives::string2char(iv,iv_bytes);
    BF_Enc bf_enc=bf.SHVE((unsigned char*)msk_bytes,(unsigned char*)iv_bytes);

    // 创建build_msg结构体，完成数据包
    struct build_msg msg;

    msg.len_of_bf=bf.get_len_of_bf();
    msg.num_of_repetitions=bf.get_num_of_repetitions();
    msg.bf_enc=bf_enc;
    msg.tab=tab;
    msg.iv=iv;

    return msg;
}



struct request_msg client::search(std::string w){
    struct request_msg msg;
    // std::vector<std::vector<std::pair<int,std::vector<std::string>>>> trapdoor;
    std::vector<int>& trapdoor=msg.trapdoor;

    // 生成陷门

    for(int k=0;k<bf.get_num_of_hashs();k++){
        // 计算h(w)，即基准点
        int h_w=bf.get_h_i_w(k,w,refresh_cnt);

        // h(w) 插入trapdoor
        trapdoor.push_back(h_w);
    }

    // 计算token
    unsigned char prefix[1];
    prefix[0]='1';
    CPRF::get_token(msk,prefix,1,msg.token);

    msg.num_of_partitions=bf.get_num_of_partitions();

    // msg.trapdoor=trapdoor;
    return msg;
}



struct refresh_msg client::refresh(std::set<std::pair<std::string,std::string>> inverted_index){
    // 更新计数器
    this->refresh_cnt+=1;

    // 重置CSC-BF
    bf.clear();

    // 重新计算布隆过滤器
    for(std::set<std::pair<std::string,std::string>>::iterator it=inverted_index.begin();it!=inverted_index.end();it++){
        // 获取w和id
        std::string w=it->first;
        std::string id=it->second;
        // 插入CSC-BF
        std::vector<int> v=bf.add(w,id,refresh_cnt);
    }

    // 计算d0
    struct refresh_msg m=bf.get_d0((unsigned char*)msk.c_str());

    return m;
}