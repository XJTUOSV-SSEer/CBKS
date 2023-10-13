#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <stdint.h>
#include <vector>
#include <algorithm>
#include <array>
#include <list>
#include <string>
#include <set>
#include <tuple>
#include <utility>
#include <unordered_map>

/* for all sources except OCALL/ECALL */



#define MSK_SIZE 32     // 主密钥32字节（256位）
#define CONCAT_SIZE 16  // 用于连接的BF[i]和i填充到16字节长
#define ALPHA_SIZE 32   // 用于对称加密的密钥alpha为32字节
#define PLAINTEXT_SIZE 16       // 对称加密中，被加密的数据0为16字节长
#define IV_SIZE 16      // AES的IV




// 字节
typedef unsigned char byte;

#endif
