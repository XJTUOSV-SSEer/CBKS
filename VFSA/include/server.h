#ifndef SERVER_H
#define SERVER_H

#include "MerkleTree.h"
#include "msg.h"

class server{
public:
    /*
        构造函数

        param:
    */
    server(MerkleTree mkt);


    /*
        根据用户发送的陷门，进行搜索

        param:
            trap_msg: 搜索陷门
        return:

    */
    struct query_result search(struct trapdoor trap_msg);

private:
    // 用户发送的索引，一棵merkle树
    MerkleTree mkt;
};


#endif