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



std::vector<std::pair<std::string,std::set<std::string>>> load_data::get_dataset(std::string filename,int w_num,int file_num){
    // 数据集
    std::vector<std::pair<std::string,std::set<std::string>>> dataset;

    FILE* fp=fopen((char*)filename.c_str(),"r");
    if(fp==NULL){
        std::cout<<"open file failed"<<std::endl;
    }
    std::string f_id;
    int w;

    for(int i=0;i<file_num;i++){
        char buf[32];
        fscanf(fp,"%s",buf);

        // 文件id
        f_id=std::string(buf);

        std::set<std::string> w_set;
        // 读取关键字集合
        for(int j=0;j<w_num;j++){
            fscanf(fp,"%d",&w);
            w_set.insert(std::to_string(w));
        }

        // 加入数据集
        dataset.push_back(std::make_pair(f_id,w_set));
    }

    fclose(fp);
    return dataset;
}




void load_data::generate_data(int file_num,int w_num,std::string filename){
    // 打开文件
    FILE* fp=fopen((char*)filename.c_str(),"w");
    if(fp==NULL){
        std::cout<<"open file failed"<<std::endl;
    }


    for(int i=0;i<file_num;i++){
        // 文件id
        std::string f_id="file"+std::to_string(i);
        std::set<int> w_set;

        fprintf(fp,"%s\n",f_id.c_str());

        // 关键字集合
        for(int j=0;j<w_num;j++){
            // 随机生成一个关键字
            int w=rand()%2000;
            while(w_set.find(w)!=w_set.end()){
                w=rand()%2000;
            }
            w_set.insert(w);

            fprintf(fp,"%d\n",w);
        }
    }

    fclose(fp);
}