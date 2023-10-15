#include <iostream>
#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/data_type.h"

int main(){
    std::vector<std::string> t;

    // 准备数据集

    // 单点数据集
    // std::set<std::pair<std::string,std::string>> inverted_index;
    // inverted_index.insert(std::make_pair("abb","301"));

    // 小数据集测试功能
    std::set<std::pair<std::string,std::string>> inverted_index=load_data::get_small_dataset();

    // 实例化client和server
    uint8_t num_of_hashs=5;
    uint16_t num_of_partitions=100;
    uint32_t len_of_bf=1000;
    uint8_t num_of_repetitions=5;
    client client1(num_of_hashs,num_of_partitions,len_of_bf,num_of_repetitions);

    // client add
    struct build_msg b_msg=client1.build(inverted_index);

    // 创建server
    server server1(b_msg);

    // client发送查询请求
    struct request_msg req_msg=client1.search("k");

    // server响应查询请求
    struct respond_msg res_msg=server1.search(req_msg);
    for(std::set<std::string>::iterator it=res_msg.res.begin();it!=res_msg.res.end();it++){
        std::cout<<(*it)<<std::endl;
    }


    return 0;
}
