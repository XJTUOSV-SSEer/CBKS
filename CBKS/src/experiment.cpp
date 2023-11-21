#include "../include/experiment.h"
#include "../include/client.h"
#include <time.h>

double experiment::experiment_token_gen(int num_of_hashs, int num_of_partitions,
                                     int len_of_bf, int num_of_repetitions)
{
    // 实例化
    client client1(num_of_hashs, num_of_partitions, len_of_bf, num_of_repetitions);

    struct timespec begin, end;

    clock_gettime(CLOCK_REALTIME, &begin);

    // 生成某个关键字的token
    client1.search("0");

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    // double elapsed = seconds * 1000 + nanoseconds / 1000000;
    double elapsed = seconds * 1000000 + nanoseconds/1000;

    return elapsed;
}