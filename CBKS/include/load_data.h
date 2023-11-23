#ifndef LOAD_DATA_H
#define LOAD_DATA_H
#include "./data_type.h"
#include<iostream>

class load_data{
public:
    /*
        生成单点数据集，只包括一个<w,in> pair
    */
    static std::set<std::pair<std::string,std::string>> get_point_dataset();

    /*
        生成一个小的数据集，包含5个文件，每个文件5个关键字
    */
    static std::set<std::pair<std::string,std::string>> get_small_dataset();


    /*
        从文件读取数据集
    */
    static std::set<std::pair<std::string,std::string>> get_dataset(std::string filename);
};

#endif