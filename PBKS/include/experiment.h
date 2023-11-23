#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <string>


class experiment{
public:
    // static int experiment_construct_1();


    /*
        实验2，测试搜索陷门生成所需的时间

        param:
            
        return:
            生成陷门所需的毫秒数
    */
    static double experiment_token_gen(int num_of_hashs,int num_of_partitions,int len_of_bf,int num_of_repetitions);

    static double experiment_search(int num_of_hashs,int num_of_partitions,int len_of_bf,int num_of_repetitions,
                                    std::string filename);
    
    /*
        实验1，测试构建索引的性能
    */
    static double experiment_build(int num_of_hashs,int num_of_partitions,int len_of_bf,int num_of_repetitions,
                                    std::string filename);
private:

};



#endif