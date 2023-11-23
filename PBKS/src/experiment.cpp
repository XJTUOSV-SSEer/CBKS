#include "../include/experiment.h"
#include "../include/client.h"
#include "../include/server.h"
#include "../include/load_data.h"
#include "../include/msg.h"
#include <time.h>

double experiment::experiment_token_gen(int num_of_hashs, int num_of_partitions,
                                        int len_of_bf, int num_of_repetitions)
{
    // 实例化
    client client1(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions);

    double sum=0;
    for (int i = 0; i < 1000; i++)
    {
        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);

        // 生成某个关键字的token
        client1.search(std::to_string(i));

        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        // double elapsed = seconds * 1000 + nanoseconds / 1000000;
        double elapsed = seconds * 1000 + nanoseconds / 1000000;
        sum+=elapsed;
    }

    return sum/1000;
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