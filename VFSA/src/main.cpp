#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"


int main(void){
    std::cout<<"---------------------start---------------------------"<<std::endl;

    // 获取数据集

    // 单点数据集
    // std::vector<std::pair<std::string,std::set<std::string>>> dataset=load_data::get_point_dataset();

    // 小数据集（10文件，每个文件5个关键字）
    std::vector<std::pair<std::string,std::set<std::string>>> dataset=load_data::get_small_dataset();


    // 初始化client
    int num_of_hashs=3;
    int len_of_bf=100;
    client c1(num_of_hashs,len_of_bf);
    MerkleTree mkt=c1.index_gen(dataset);

    // 初始化server
    server s1(mkt);

    // 生成陷门
    std::string w="s";
    struct trapdoor trap=c1.trap_gen(w);


    // server查询
    struct query_result qr=s1.search(trap);



    // client验证
    c1.verify_result(w,qr);

    std::cout<<"----------------------end------------------------------"<<std::endl;

    return 0;

    
}