#include <iostream>
#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/data_type.h"
#include "../include/experiment.h"


int main_old(){
    std::vector<std::string> t;

    // 准备数据集
    //  单点数据集
    // std::set<std::pair<std::string,std::string>> inverted_index=load_data::get_point_dataset();

    // 小数据集测试功能
    // std::set<std::pair<std::string,std::string>> inverted_index=load_data::get_small_dataset();

    // 数据集
    std::set<std::pair<std::string,std::string>> inverted_index=load_data::get_dataset("../../dataset/10K.txt");

    // 实例化client和server
    uint8_t num_of_hashs=3;
    uint16_t num_of_partitions=1000;
    uint32_t len_of_bf=100000;
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
    std::cout<<std::endl;


    // 第1次refresh
    struct refresh_msg r_msg=client1.refresh(inverted_index);
    server1.refresh(r_msg);
    // 搜索
    req_msg=client1.search("0");
    res_msg=server1.search(req_msg);
    std::cout<<res_msg.res.size()<<std::endl;
    for(std::set<std::string>::iterator it=res_msg.res.begin();it!=res_msg.res.end();it++){
        // std::cout<<(*it)<<std::endl;
        std::cout<<(*it)<<" ";
    }
    std::cout<<std::endl;

    // 第2次refresh
    client1.refresh(inverted_index);
    r_msg=client1.refresh(inverted_index);
    server1.refresh(r_msg);
    // 搜索
    req_msg=client1.search("0");
    res_msg=server1.search(req_msg);
    res_msg=server1.search(req_msg);
    std::cout<<res_msg.res.size()<<std::endl;
    for(std::set<std::string>::iterator it=res_msg.res.begin();it!=res_msg.res.end();it++){
        // std::cout<<(*it)<<std::endl;
        std::cout<<(*it)<<" ";
    }
    std::cout<<std::endl;

    return 0;
}


int main(){
    // 功能测试
    // main_old();



    // 对比基于对称加密的PRF与CPRF的加密速度
    // experiment::experiment_PRF();



    // 实验1
    // 1.1
    // double t=0;
    // t=experiment::experiment_build(3,100,650000,5,"../../dataset/10K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,5,"../../dataset/50K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,5,"../../dataset/150K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,5,"../../dataset/200K.txt");
    // std::cout<<t<<"ms"<<std::endl;

    // 1.2
    // double t=0;
    // t=experiment::experiment_build(3,100,200000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,400000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,600000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,800000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,1000000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;


    // 1.3
    // double t=0;
    // t=experiment::experiment_build(3,100,650000,2,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,3,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,4,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,100,650000,6,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;

    // 1.4
    // double t=0;
    // t=experiment::experiment_build(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,200,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,300,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,400,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_build(3,500,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;




    // 实验2
    // 实验2.1
    // double t=0;
    // t=experiment::experiment_token_gen(3,100,200000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,400000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,600000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,800000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,1000000,5);
    // std::cout<<t<<"us"<<std::endl;

    // 2.2
    // double t=0;
    // t=experiment::experiment_token_gen(3,100,650000,2);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,650000,3);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,650000,4);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,650000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,100,650000,6);
    // std::cout<<t<<"us"<<std::endl;


    // 2.3
    // double t=0;
    // t=experiment::experiment_token_gen(3,100,650000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,200,650000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,300,650000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,400,650000,5);
    // std::cout<<t<<"us"<<std::endl;
    // t=experiment::experiment_token_gen(3,500,650000,5);
    // std::cout<<t<<"us"<<std::endl;




    // 实验3
    // 3.1
    // double t=experiment::experiment_search(3,100,650000,5,"../../dataset/10K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,5,"../../dataset/50K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,5,"../../dataset/150K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,5,"../../dataset/200K.txt");
    // std::cout<<t<<"ms"<<std::endl;
  
    // 3.2
    // double t=0;
    // t=experiment::experiment_search(3,100,200000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,400000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,600000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,800000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,1000000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;

    // 3.3
    // double t=0;
    // t=experiment::experiment_search(3,100,650000,2,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,3,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,4,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,100,650000,6,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;

    // 3.4
    // double t=0;
    // t=experiment::experiment_search(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,200,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,300,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,400,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_search(3,500,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;


    // 实验4
    // 4.1
    // double t=0;
    // t=experiment::experiment_refresh(3,100,650000,5,"../../dataset/10K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_refresh(3,100,650000,5,"../../dataset/50K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_refresh(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_refresh(3,100,650000,5,"../../dataset/150K.txt");
    // std::cout<<t<<"ms"<<std::endl;
    // t=experiment::experiment_refresh(3,100,650000,5,"../../dataset/200K.txt");
    // std::cout<<t<<"ms"<<std::endl;


    // 4.2
    double t=0;
    t=experiment::experiment_refresh(3,100,200000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,400000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,600000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,800000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,1000000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;


    // 4.3
    // double t=0;
    t=experiment::experiment_refresh(3,100,650000,2,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,650000,3,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,650000,4,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,650000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,100,650000,6,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;

    // 4.4
    t=experiment::experiment_refresh(3,100,650000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,200,650000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,300,650000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,400,650000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    t=experiment::experiment_refresh(3,500,650000,5,"../../dataset/100K.txt");
    std::cout<<t<<"ms"<<std::endl;
    

    // 实验5
    // 5.1
    // double t=0;
    // t=experiment::experiment_acc(3,1000,650000,2,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1000,650000,3,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1000,650000,4,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1000,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1000,650000,6,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;



    // 5.2
    // double t=0;
    // t=experiment::experiment_acc(3,100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,200,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,300,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,400,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,500,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,600,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,700,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,800,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,900,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1000,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1100,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1200,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1300,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1400,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1500,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1600,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1700,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1800,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,1900,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;
    // t=experiment::experiment_acc(3,2000,650000,5,"../../dataset/100K.txt");
    // std::cout<<t<<std::endl;


    return 0;
}






