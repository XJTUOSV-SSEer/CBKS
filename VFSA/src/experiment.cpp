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
    for (int i = 0; i < 5; i++)
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

    return sum / 5;
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

    // client计算陷门，server进行搜索
    double sum = 0;
    for (int i = 0; i < 1000; i++)
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

    return sum / 1000;
}



double experiment::experiment_acc(int num_of_hashs,int len_of_bf,std::string filename,int w_num,int file_num){
    
}