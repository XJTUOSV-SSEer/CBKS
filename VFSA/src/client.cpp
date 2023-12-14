#include "../include/client.h"
#include "../include/Twin_BloomFilter.h"
#include "../include/MerkleTree.h"
#include "../include/MultisetAccumulator.h"



client::client(int num_of_hashs,int len_of_bf,std::vector<std::pair<std::string,std::set<std::string>>> dataset){
    this->num_of_hashs=num_of_hashs;
    this->len_of_bf=len_of_bf;

    // 创建累加器MSA
    MultisetAccumulator msa;

    // 创建merkle树
    MerkleTree mkt;

    // 处理每个文件
    for(int i=0;i<dataset.size();i++){
        // 文件id
        std::string f_id=dataset[i].first;
        // 关键字集合
        std::set<std::string> w_set=dataset[i].second;

        // 对每个文件，生成一个merkle树的叶结点，然后计算对应的tbf,acc,P_T
        struct node leaf(len_of_bf,num_of_hashs);
        leaf.is_leaf=true;

        // 计算tbf
        for(std::set<std::string>::iterator it=w_set.begin();it!=w_set.end();it++){
            std::string w=(*it);
            // 将关键字加入tbf
            leaf.tbf.add(w);
        }

        // 计算P_T
        leaf.P_T=msa.get_product(w_set);

        // 计算acc
        leaf.acc=msa.get_acc(w_set);

        // 计算digest
        leaf.get_leaf_digest();

        // 将叶结点加入merkle树
        mkt.tree.push_back(leaf);
    }

    // 构建merkle树

}