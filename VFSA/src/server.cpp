#include "../include/MerkleTree.h"
#include "../include/server.h"



server::server(MerkleTree mkt):mkt(mkt){

}



struct query_result server::search(struct trapdoor trap_msg){
    std::string& x=trap_msg.x;
    std::vector<int>& locs=trap_msg.locs;

    // 对merkle树进行遍历，从而实现查询
    struct query_result qr=mkt.query(x,locs);

    return qr;
}