#include "../include/load_data.h"

std::set<std::pair<std::string,std::string>> load_data::get_small_dataset(){
    std::set<std::pair<std::string,std::string>> res;
    
    std::vector<std::string> v;
    v.push_back("");
    v.push_back("abcde");
    v.push_back("fgcah");
    v.push_back("higkb");
    v.push_back("acezm");
    v.push_back("nmaqr");

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