#ifndef CLIENT_H
#define CLIENT_H

#include <set>
#include <string>
#include <vector>

/*
    client类
*/
class client{
public:
    /*
        初始化对象。将多个文件的内容转换为TBF，然后组织成一棵Merkle树

        param:
            num_of_hashs:
            len_of_bf:
            dataset: 数据集。vector中每个元素是一个pair，pair第一个成员为文件名，第二个成员为一个set储存文件中所有关键字
    */
    client(int num_of_hashs,int len_of_bf,std::vector<std::pair<std::string,std::set<std::string>>> dataset);




private:
    // TBF中哈希函数的数量
    int num_of_hashs;
    // TBF的长度
    int len_of_bf;
    // 
};


#endif