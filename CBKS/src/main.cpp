#include <iostream>
#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/data_type.h"
#include "../include/experiment.h"


int main(){
    // 实验2.1
    double sum=0;
    for(int i=0;i<100;i++){
        sum+=experiment::experiment_token_gen(3,1000,650000,5);
    }
    std::cout<<sum/100<<std::endl;


    
}





int main_old(){
    std::vector<std::string> t;

    // 准备数据集
    // 小数据集测试功能
    // std::set<std::pair<std::string,std::string>> inverted_index=load_data::get_small_dataset();

    // 数据集
    std::set<std::pair<std::string,std::string>> inverted_index=load_data::get_dataset("../../dataset/10K.txt");

    // 实例化client和server
    uint8_t num_of_hashs=3;
    uint16_t num_of_partitions=1000;
    uint32_t len_of_bf=1000000;
    uint8_t num_of_repetitions=5;
    client client1(num_of_hashs,num_of_partitions,len_of_bf,num_of_repetitions);

    // client add
    struct build_msg b_msg=client1.build(inverted_index);

    // 创建server
    server server1(b_msg);

    // client发送查询请求
    struct request_msg req_msg=client1.search("0");

    // server响应查询请求
    struct respond_msg res_msg=server1.search(req_msg);
    std::cout<<res_msg.res.size()<<std::endl;
    for(std::set<std::string>::iterator it=res_msg.res.begin();it!=res_msg.res.end();it++){
        // std::cout<<(*it)<<std::endl;
        std::cout<<(*it)<<" ";
    }

    return 0;
}
