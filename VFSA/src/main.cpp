#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/experiment.h"


// int main(void){
//     // 生成不同规模的数据集。固定200个文件

//     // // 10K
//     // load_data::generate_data(200,50,"../dataset/10K.txt");

//     // // 50K
//     // load_data::generate_data(200,250,"../dataset/50K.txt");

//     // // 100K
//     // load_data::generate_data(200,500,"../dataset/100K.txt");


//     // // 150K
//     // load_data::generate_data(200,750,"../dataset/150K.txt");


//     // // 200K
//     // load_data::generate_data(200,1000,"../dataset/200K.txt");

//     // 1K
//     load_data::generate_data(200,5,"../dataset/1K.txt");

//     // 5K
//     load_data::generate_data(200,25,"../dataset/5K.txt");
    
//     // 10K
//     load_data::generate_data(200,50,"../dataset/10K.txt");

//     // 15K
//     load_data::generate_data(200,75,"../dataset/15K.txt");

//     // 20K
//     load_data::generate_data(200,100,"../dataset/20K.txt");

    
// }



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



int main(void){
    // 1.1
    // std::cout<<experiment::experiment_build(3,650,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,650,"../dataset/50K.txt",250,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,650,"../dataset/100K.txt",500,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,650,"../dataset/150K.txt",750,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,650,"../dataset/200K.txt",1000,200)<<std::endl;

    // 1.2
    // std::cout<<experiment::experiment_build(3,200,"../dataset/100K.txt",500,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,400,"../dataset/100K.txt",500,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,600,"../dataset/100K.txt",500,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,800,"../dataset/100K.txt",500,200)<<std::endl;
    // std::cout<<experiment::experiment_build(3,1000,"../dataset/100K.txt",500,200)<<std::endl;


    // 2.1 测试BF长度对陷门生成时间的影响
    // std::cout<<experiment::experiment_token_gen(3,200)<<std::endl;
    // std::cout<<experiment::experiment_token_gen(3,400)<<std::endl;
    // std::cout<<experiment::experiment_token_gen(3,600)<<std::endl;
    // std::cout<<experiment::experiment_token_gen(3,800)<<std::endl;
    // std::cout<<experiment::experiment_token_gen(3,1000)<<std::endl;

    // 3.1
    // std::cout<<experiment::experiment_search(3,650,"../dataset/10K.txt",50,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/50K.txt",250,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/100K.txt",500,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/150K.txt",750,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/200K.txt",1000,200)<<"ms"<<std::endl;

    // std::cout<<experiment::experiment_search(3,650,"../dataset/1K.txt",5,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/5K.txt",25,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/10K.txt",50,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/15K.txt",75,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,650,"../dataset/20K.txt",100,200)<<"ms"<<std::endl;

    // 3.2
    // std::cout<<experiment::experiment_search(3,200,"../dataset/20K.txt",100,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,400,"../dataset/20K.txt",100,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,600,"../dataset/20K.txt",100,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,800,"../dataset/20K.txt",100,200)<<"ms"<<std::endl;
    // std::cout<<experiment::experiment_search(3,1000,"../dataset/20K.txt",100,200)<<"ms"<<std::endl;
    
    // 5.1
    // std::cout<<experiment::experiment_acc(3,200,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_acc(3,300,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_acc(3,400,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_acc(3,500,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_acc(3,600,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_acc(3,700,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_acc(3,800,"../dataset/10K.txt",50,200)<<std::endl;
    // std::cout<<experiment::experiment_acc(3,900,"../dataset/10K.txt",50,200)<<std::endl;
    std::cout<<experiment::experiment_acc(3,1000,"../dataset/10K.txt",50,200)<<std::endl;
}
