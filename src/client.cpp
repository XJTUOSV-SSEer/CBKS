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

struct build_msg client::build(std::set<std::pair<std::string, std::string>> inverted_index)
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
    std::vector<std::vector<std::pair<int,std::vector<std::string>>>>& trapdoor=msg.trapdoor;

    // 生成陷门
    for(int r=0;r<bf.get_num_of_repetitions();r++){
        // 每个repetition对应一个vector<pair<int,vector<string>>>
        std::vector<std::pair<int,std::vector<std::string>>> vec_r;

        for(int k=0;k<bf.get_num_of_hashs();k++){
            // 计算h(w)，即基准点
            int h_w=bf.get_h_i_w(k,w);
            // 储存b个PRF
            std::vector<std::string> prfs;
            // 从h_w开始生成后b个位置的PRF
            for(int i=0;i<bf.get_num_of_partitions();i++){
                // s1="0000000000000001"
                std::string s1="";
                s1.resize(CONCAT_SIZE);
                fill(s1.begin(),s1.end(),'0');
                s1[CONCAT_SIZE-1]='1';
                // s2
                std::string s2=std::to_string((h_w+i)%(bf.get_len_of_bf()));
                std::string s3="";
                s3.resize(CONCAT_SIZE-s2.length());
                fill(s3.begin(),s3.end(),'0');
                s2=s3.append(s2);
                // 1||h(w)+i
                std::string data=s1.append(s2);

                // 为PRF值分配空间
                char v[ALPHA_SIZE];
                Crypto_Primitives::get_prf((unsigned char*)(msk.c_str()),
                (unsigned char*)(data.c_str()),data.length(),(unsigned char*)v);

                // 将PRF加入vector prfs
                prfs.push_back(std::string(v));
            }
            // 生成pair
            std::pair<int,std::vector<std::string>> p=std::make_pair(h_w,prfs);
            // 加入vec_r
            vec_r.push_back(p);

        }

        // 将一个repetition的数据加入trapdoor
        trapdoor.push_back(vec_r);
    }

    return msg;
}