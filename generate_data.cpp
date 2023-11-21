#include <stdlib.h>
#include <set>
#include <map>
#include <cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

/*
    生成数据集
    param:
        num_of_w：不同关键字的个数
        num_of_id：每个关键字对应的文件id的个数
        dataset：一个映射表，key为w，value为id的集合
*/
void generate_data(int num_of_w,int num_of_id,std::map<int,std::set<int>>& dataset){
    for(int i=0;i<num_of_w;i++){
        // 为了防止生成的id重复，使用set去重
        while(dataset[i].size()<num_of_id){
            // 随机生成一个id
            int n=rand()%5000;
            dataset[i].insert(n);
        }
    }
}


/*
    将数据集转换为std::set<std::pair<int,int>>，即<w,id>对的集合，然后写入文件
    param:
        dataset:数据集
        filename:要写入的文件名
*/
void write_to_file(std::map<int,std::set<int>>& dataset,std::string filename){
    FILE* fp=fopen((char*)filename.c_str(),"w");
    if(fp==NULL){
        std::cout<<"open file failed"<<std::endl;
        return;
    }



    // 数据集转换
    std::set<std::pair<int,int>> s;
    for(std::map<int,std::set<int>>::iterator it=dataset.begin();it!=dataset.end();it++ ){
        int w=it->first;
        std::set<int>& ids=it->second;
        for(std::set<int>::iterator j=ids.begin();j!=ids.end();j++){
            int id=*j;
            s.insert(std::make_pair(w,id));
            // 写入到文件
            fprintf(fp,"%d %d\n",w,id);
        }
    }   

    fclose(fp);
}


int main(void){
    // 生成10000大小数据集，即20个w，每个w对应500个id
    std::map<int,std::set<int>> dataset;
    generate_data(20,500,dataset);
    write_to_file(dataset,"./dataset/10K.txt");

    // 生成50000大小数据集，即100个w，每个w对应500个id
    dataset.clear();
    generate_data(100,500,dataset);
    write_to_file(dataset,"./dataset/50K.txt");

    // 生成100000大小数据集，即200个w，每个w对应500个id
    dataset.clear();
    generate_data(200,500,dataset);
    write_to_file(dataset,"./dataset/100K.txt");

    // 生成150000大小数据集，即300个w，每个w对应500个id
    dataset.clear();
    generate_data(300,500,dataset);
    write_to_file(dataset,"./dataset/150K.txt");

    // 生成200000大小数据集，即400个w，每个w对应500个id
    dataset.clear();
    generate_data(400,500,dataset);
    write_to_file(dataset,"./dataset/200K.txt");
}