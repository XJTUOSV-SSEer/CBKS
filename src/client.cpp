#include "../include/client.h"
#include "../include/Crypto_Primitives.h"

client::client(uint8_t num_of_hashs,
               uint16_t num_of_partitions,
               uint32_t len_of_bf,
               uint8_t num_of_repetitions) : bf(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions)
{
    // 随机生成主密钥
    msk="XJTU-OSV-MSK0000000000000000000";
    // msk = Crypto_Primitives::get_rand(MSK_SIZE);

    // 固定的IV
    iv="XJTU-OSV-IV1234";
    // iv = Crypto_Primitives::get_rand(IV_SIZE);
}

std::vector<std::vector<std::set<std::string>>> client::insert_data(
    std::set<std::pair<std::string, std::string>> inverted_index)
{
    // 创建哈希表（后续发送至服务器）
    std::vector<std::vector<std::set<std::string>>> tab;
    // 预留空间
    for(int i=0;i<bf.get_num_of_repetitions();i++){
        std::vector<std::set<std::string>> tmp;
        tmp.resize(bf.get_len_of_bf());
        tab.push_back(tmp);
    }

    // 遍历倒排索引进行处理
    for(std::set<std::pair<std::string,std::string>>::iterator it=inverted_index.begin();it!=inverted_index.end();it++){
        // 获取w和id
        std::string w=it->first;
        std::string id=it->second;
        // 插入CSC-BF
        std::vector<int> v=bf.add(w,id);

        // 更新哈希表
        for(int r=0;r<v.size();r++){
            int b=v[r];
            // 将id加入tab[r][b]对应的集合
            (tab[r][b]).insert(id);
        }

    }


    // 加密CSC-BF
    BF_Enc bf_enc=bf.SHVE((unsigned char*)(msk.c_str()),(unsigned char*)(iv.c_str()));

    return tab;
}