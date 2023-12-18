#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <string>


class experiment{
public:
    // static int experiment_construct_1();

    /*
        实验1，测试构建索引的性能
    */
    static double experiment_build(int num_of_hashs,int len_of_bf, std::string filename,int w_num,int file_num);


    /*
        实验2，测试搜索陷门生成所需的时间

        param:
            filename:数据集的文件名
        return:
            生成陷门所需的微秒数
    */
    static double experiment_token_gen(int num_of_hashs,int len_of_bf);

    
    static double experiment_search(int num_of_hashs,int len_of_bf,std::string filename,int w_num,int file_num);


    static double experiment_acc(int num_of_hashs,int len_of_bf,std::string filename,int w_num,int file_num);
};



#endif