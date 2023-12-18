#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/experiment.h"


int main(void){
    // 生成不同规模的数据集。固定每个文件包含100个关键字

    // 10K
    load_data::generate_data(100,100,"../dataset/10K.txt");

    // 50K
    load_data::generate_data(500,100,"../dataset/50K.txt");

    // 100K
    load_data::generate_data(1000,100,"../dataset/100K.txt");


    // 150K
    load_data::generate_data(1500,100,"../dataset/150K.txt");


    // 200K
    load_data::generate_data(2000,100,"../dataset/200K.txt");
}



// int main(void){
//     std::cout<<"---------------------start---------------------------"<<std::endl;

//     // 获取数据集

//     // 单点数据集
//     // std::vector<std::pair<std::string,std::set<std::string>>> dataset=load_data::get_point_dataset();

//     // 小数据集（10文件，每个文件5个关键字）
//     // std::vector<std::pair<std::string,std::set<std::string>>> dataset=load_data::get_small_dataset();

//     // 实验用数据集
//     std::vector<std::pair<std::string,std::set<std::string>>> dataset;
//     dataset=load_data::get_dataset("../dataset/10K.txt",100,100);


//     // 初始化client
//     int num_of_hashs=5;
//     int len_of_bf=650;
//     client c1(num_of_hashs,len_of_bf);
//     MerkleTree mkt=c1.index_gen(dataset);

//     std::cout<<"Generate Index succed"<<std::endl;

//     // 初始化server
//     server s1(mkt);

//     // 生成陷门
//     std::string w="1";
//     struct trapdoor trap=c1.trap_gen(w);


//     std::cout<<"Generate Trapdoor succed"<<std::endl;


//     // server查询
//     struct query_result qr=s1.search(trap);


//     std::cout<<"Query succed"<<std::endl;



//     // client验证
//     c1.verify_result(w,qr);


//     std::cout<<"Verify succed"<<std::endl;

//     std::cout<<"----------------------end------------------------------"<<std::endl;

//     return 0;

    
// }



// int main(void){
//     std::cout<<experiment::experiment_build(3,650,"../dataset/10K.txt",100,100)<<std::endl;
//     std::cout<<experiment::experiment_build(3,650,"../dataset/50K.txt",100,500)<<std::endl;
//     std::cout<<experiment::experiment_build(3,650,"../dataset/100K.txt",100,1000)<<std::endl;
//     std::cout<<experiment::experiment_build(3,650,"../dataset/150K.txt",100,1500)<<std::endl;
//     std::cout<<experiment::experiment_build(3,650,"../dataset/200K.txt",100,2000)<<std::endl;
// }