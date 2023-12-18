#ifndef LOAD_DATA_H
#define LOAD_DATA_H
#include "./data_type.h"
#include<iostream>
#include<vector>
#include<set>

class load_data{
public:
    /*
        生成单点数据集，只包括一个<w,id> pair
    */
    static std::vector<std::pair<std::string,std::set<std::string>>> get_point_dataset();

    /*
        生成一个小的数据集，包含5个文件，每个文件5个关键字
    */
    static std::vector<std::pair<std::string,std::set<std::string>>> get_small_dataset();


    /*
        从文件读取数据集。每个文件id对应w_num个关键字
    */
    static std::vector<std::pair<std::string,std::set<std::string>>> get_dataset(std::string filename,int w_num,int file_num);


    /*
        随机生成file_num个文件，每个文件包含w_num个关键字，并将数据储存在filename文件中
        

    */
    static void generate_data(int file_num,int w_num,std::string filename);
};

#endif