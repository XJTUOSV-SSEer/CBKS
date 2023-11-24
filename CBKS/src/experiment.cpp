#include "../include/experiment.h"
#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/msg.h"
#include "../include/Crypto_Primitives.h"
#include "../include/CPRF.h"
#include "../include/data_type.h"
#include <time.h>


#define CORRECT_NUMBER 500

double experiment::experiment_token_gen(int num_of_hashs, int num_of_partitions,
                                        int len_of_bf, int num_of_repetitions)
{
    // 实例化
    client client1(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions);

    struct timespec begin, end;

    double sum = 0;
    for (int i = 0; i < 10000; i++)
    {
        clock_gettime(CLOCK_REALTIME, &begin);

        // 生成某个关键字的token
        client1.search("0");

        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        // double elapsed = seconds * 1000 + nanoseconds / 1000000;
        double elapsed = seconds * 1000000 + nanoseconds / 1000;
        sum+=elapsed;
    }

    return sum/10000;
}

double experiment::experiment_search(int num_of_hashs, int num_of_partitions, int len_of_bf,
                                     int num_of_repetitions, std::string filename)
{
    // 读数据
    std::set<std::pair<std::string, std::string>> dataset = load_data::get_dataset(filename);

    // 实例化client
    client client1(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions);
    struct build_msg b_msg = client1.build(dataset);

    // server
    server server1(b_msg);

    // client计算陷门，server进行搜索
    double sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        struct request_msg trapdoor = client1.search(std::to_string(i));
        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);
        server1.search(trapdoor);
        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds * 1000 + nanoseconds / 1000000;
        sum += elapsed;
    }

    return sum / 1000;
}

double experiment::experiment_PRF()
{
    std::string msg = "12345678901234567890";
    char key_bytes[MSK_SIZE] = {'0'};
    std::string key = std::string(key_bytes, MSK_SIZE);
    char value[PRF_SIZE] = {0};

    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    // 使用基于对称加密的PRF
    for (int i = 0; i < 1000000; i++)
    {
        Crypto_Primitives::get_prf((unsigned char *)key_bytes, (unsigned char *)msg.c_str(), msg.length(), (unsigned char *)value);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds * 1000 + nanoseconds / 1000000;
    std::cout << elapsed << "ms" << std::endl;

    // 使用GGM PRF
    std::string msg2 = "123";
    clock_gettime(CLOCK_REALTIME, &begin);
    for (int i = 0; i < 1000000; i++)
    {
        CPRF::prf(key, (unsigned char *)msg2.c_str(), msg2.length(), (unsigned char *)value);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    seconds = end.tv_sec - begin.tv_sec;
    nanoseconds = end.tv_nsec - begin.tv_nsec;
    elapsed = seconds * 1000 + nanoseconds / 1000000;
    std::cout << elapsed << "ms" << std::endl;
    return 0;
}

double experiment::experiment_build(int num_of_hashs, int num_of_partitions, int len_of_bf, int num_of_repetitions,
                                    std::string filename)
{
    // 读数据
    std::set<std::pair<std::string, std::string>> dataset = load_data::get_dataset(filename);

    double sum = 0;
    for (int i = 0; i < 5; i++)
    {
        // 实例化client
        client client1(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions);

        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);

        struct build_msg b_msg = client1.build(dataset);

        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds * 1000 + nanoseconds / 1000000;
        sum += elapsed;
    }

    return sum / 5;
}


double experiment::experiment_refresh(int num_of_hashs, int num_of_partitions, int len_of_bf, int num_of_repetitions,
                        std::string filename)
{
    // 读数据
    std::set<std::pair<std::string, std::string>> dataset = load_data::get_dataset(filename);

    double sum=0;
    // 实例化client
    client client1(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions);
    struct build_msg b_msg = client1.build(dataset);
    // server
    server server1(b_msg);

    for(int i=0;i<5;i++){
        struct timespec begin, end;

        clock_gettime(CLOCK_REALTIME, &begin);

        struct refresh_msg r_msg=client1.refresh(dataset);
        // server1.refresh(r_msg);

        clock_gettime(CLOCK_REALTIME, &end);
        

        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds*1000 + nanoseconds/1000000;
        sum+=elapsed;
    }

    return sum/5;
}



double experiment::experiment_acc(int num_of_hashs,int num_of_partitions,int len_of_bf,int num_of_repetitions,
                                    std::string filename)
{
    // 读数据
    std::set<std::pair<std::string, std::string>> dataset = load_data::get_dataset(filename);

    // 关键字的个数
    int num_of_kw=200;

    

    // 记录多次实验的acc之和
    double sum=0;
    // 实例化client
    client client1(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions);
    struct build_msg b_msg = client1.build(dataset);
    // server
    server server1(b_msg);

    // 对所有关键字都搜索一次，得到的acc取均值    
    for(int i=0;i<num_of_kw;i++){
        std::string kw=std::to_string(i);

        struct request_msg req_m=client1.search(kw);
        struct respond_msg res_m =server1.search(req_m);
        std::set<std::string>& query_res=res_m.res;
        
        // 检验正确性
        // 关键字"0"对应的正确结果correct_res
        std::set<std::string> correct_res;
        for(std::set<std::pair<std::string,std::string>>::iterator it=dataset.begin();it!=dataset.end();it++){
            if((it->first)==kw){
                correct_res.insert(it->second);
            }
        }
        // correct_res与query_res求交集
        std::set<std::string> tmp;
        std::set_intersection(query_res.begin(),query_res.end(),correct_res.begin(),correct_res.end(),
                            std::insert_iterator<std::set<std::string>>(tmp,tmp.begin()));
        double acc=(double)CORRECT_NUMBER/(double)(query_res.size());
        sum+=acc;
        // std::cout<<tmp.size()<<" "<<query_res.size()<<" "<<acc<<std::endl;
    }

    return sum/num_of_kw;
}