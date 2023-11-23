#include "../include/load_data.h"

std::set<std::pair<std::string,std::string>> load_data::get_point_dataset(){
    std::set<std::pair<std::string,std::string>> res;
    std::string w="a";
    std::string id="0";

    res.insert(std::make_pair(w,id));
    return res;
}



std::set<std::pair<std::string,std::string>> load_data::get_small_dataset(){
    std::set<std::pair<std::string,std::string>> res;
    
    std::vector<std::string> v;
    v.push_back("");
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
    // for(int i=1;i<2;i++){
        std::string id=std::to_string(i);
        for(int j=0;j<v[i].length();j++){
            std::string w=std::string(1,v[i][j]);
            res.insert(std::make_pair(w,id));
        }
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