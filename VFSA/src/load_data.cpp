#include "../include/load_data.h"
#include<set>

std::vector<std::pair<std::string,std::set<std::string>>> load_data::get_point_dataset(){
    std::vector<std::pair<std::string,std::set<std::string>>> dataset;

    // f0:0,1
    std::string f_id="f0";
    std::set<std::string> w_set;
    w_set.insert("1");
    w_set.insert("0");
    dataset.push_back(std::make_pair(f_id,w_set));


    // f1:1,2
    f_id="f1";
    w_set.clear();
    w_set.insert("1");
    w_set.insert("2");
    dataset.push_back(std::make_pair(f_id,w_set));
    
    return dataset;
}



std::vector<std::pair<std::string,std::set<std::string>>> load_data::get_small_dataset(){
    std::vector<std::pair<std::string,std::set<std::string>>> res;
    
    std::vector<std::string> v;
    v.push_back("");
    // 10个文件
    v.push_back("abcde");
    v.push_back("fgcah");
    v.push_back("higkb");
    v.push_back("acezm");
    v.push_back("nmaqr");
    v.push_back("fhpqy");
    v.push_back("oruvy");
    v.push_back("prstz");
    v.push_back("ghikr");
    v.push_back("dhlng");


    for(int i=1;i<v.size();i++){
        std::string f_id="f"+std::to_string(i);
        std::set<std::string> w_set;
        for(int j=0;j<v[i].length();j++){
            std::string w=std::string(1,v[i][j]);
            w_set.insert(w);
        }
        res.push_back(std::make_pair(f_id,w_set));
    }
    return res;
}



std::set<std::pair<std::string,std::string>> load_data::get_dataset(std::string filename){
    std::set<std::pair<std::string,std::string>> dataset;

    FILE* fp=fopen((char*)filename.c_str(),"r");
    if(fp==NULL){
        std::cout<<"open file failed"<<std::endl;
    }
    int w;
    int id;
    while(fscanf(fp,"%d %d",&w,&id)!=EOF){
        dataset.insert(std::make_pair(std::to_string(w),std::to_string(id)));
    }

    fclose(fp);
    return dataset;
}