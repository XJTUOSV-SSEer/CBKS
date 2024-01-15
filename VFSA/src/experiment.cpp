#include "../include/experiment.h"
#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/msg.h"
#include "../include/Crypto_Primitives.h"
#include "../include/data_type.h"
#include "../include/MerkleTree.h"
#include <time.h>


#define CORRECT_NUMBER 500



double experiment::experiment_build(int num_of_hashs,int len_of_bf, std::string filename,int w_num,int file_num)
{
    // 读数据
    std::vector<std::pair<std::string, std::set<std::string>>> dataset = load_data::get_dataset(filename,w_num,file_num);

    double sum = 0;
    for (int i = 0; i < 1; i++)
    {
        // 实例化client
        client client1(num_of_hashs,len_of_bf);

        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);

        MerkleTree mkt = client1.index_gen(dataset);

        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds * 1000 + nanoseconds / 1000000;
        sum += elapsed;
    }

    return sum / 1;
}



double experiment::experiment_token_gen(int num_of_hashs,int len_of_bf)
{
    // 实例化
    client client1(num_of_hashs,len_of_bf);

    struct timespec begin, end;

    double sum = 0;
    for (int i = 0; i < 10000; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);

        // 生成某个关键字的token
        client1.trap_gen(std::to_string(i));

        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        // double elapsed = seconds * 1000 + nanoseconds / 1000000;
        double elapsed = seconds * 1000000 + nanoseconds / 1000;
        sum+=elapsed;
    }

    return sum/10000;
}


double experiment::experiment_search(int num_of_hashs,int len_of_bf,std::string filename,int w_num,int file_num)
{
    // 读数据
    std::vector<std::pair<std::string, std::set<std::string>>> dataset = load_data::get_dataset(filename,w_num,file_num);

    // 实例化client
    client client1(num_of_hashs,len_of_bf);
    MerkleTree mkt=client1.index_gen(dataset);

    // server
    server server1(mkt);


    std::cout<<"------build--------"<<std::endl;

    // client计算陷门，server进行搜索
    double sum = 0;
    for (int i = 0; i < 10; i++)
    {
        struct trapdoor trap = client1.trap_gen(std::to_string(i));
        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);
        server1.search(trap);
        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds * 1000 + nanoseconds / 1000000;
        sum += elapsed;
    }

    return sum / 10;
}



double experiment::experiment_acc(int num_of_hashs,int len_of_bf,std::string filename,int w_num,int file_num){
    // 读数据
    std::vector<std::pair<std::string, std::set<std::string>>> dataset = load_data::get_dataset(filename,w_num,file_num);

    // build
    client client1(num_of_hashs,len_of_bf);
    MerkleTree mkt=client1.index_gen(dataset);

    // server
    server server1(mkt);

    std::cout<<"----------------build------------------"<<std::endl;

    // 要查询的关键字个数
    int num_of_kw=100;

    // 关键字范围为0-999
    // 对关键字0-100进行搜索，计算平均acc
    double acc=0;
    for(int i=0;i<=num_of_kw;i++){
        std::string w_to_query=std::to_string(i);
        struct trapdoor trap = client1.trap_gen(w_to_query);

        struct timespec begin, end;
        
        // 搜索
        struct query_result qr=server1.search(trap);
        // 搜索结果中的匹配元素
        std::set<std::string> query_set;
        std::vector<struct proof_node>& res=qr.res;
        for(int i=0;i<res.size();i++){
            struct proof_node& pn = res[i];
            // 验证匹配的叶结点,判断关键字是否真正存在
            if(pn.is_match && pn.is_leaf){
                query_set.insert(pn.f_id);
            }            
        }

        // 遍历数据集获取正确的结果储存为correct_set
        std::set<std::string> correct_set;
        for(int i=0;i<dataset.size();i++){
            // 文件名
            std::string f=(dataset[i]).first;
            std::set<std::string>& w_set=(dataset[i]).second;
            // 判断关键字是否在该文件中
            if(w_set.find(w_to_query)!=w_set.end()){
                correct_set.insert(f);
            }
        }

        // 计算准确率
        acc+=(double)(correct_set.size())/(double)(query_set.size());       

    }

    return acc/(double)num_of_kw;
}