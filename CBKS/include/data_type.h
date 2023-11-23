#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <stdint.h>
#include <vector>
#include <algorithm>
#include <array>
#include <string>
#include <set>
#include <cstring>
#include <unordered_map>

/* for all sources except OCALL/ECALL */



#define MSK_SIZE 32     // 主密钥32字节（256位）
#define CONCAT_SIZE 16  // PBKS中，用于连接的BF[i]和i都填充到16字节长
#define ALPHA_SIZE 32   // 用于对称加密的密钥alpha为32字节
#define PLAINTEXT_SIZE 16       // 对称加密中，被加密的数据0为16字节长
#define IV_SIZE 16      // AES的IV
#define PRF_SIZE 32     // PRF值32字节
#define TOKEN_SIZE 32   // token32字节
#define CPRF_DATA_SIZE 4  // CBKS中，使用CPRF时，CPRF的数据为BF[i]||i，共17字节
#define CPRF_POS_SIZE 3   // CBKS中，使用CPRF时，使用3个字节表示位置



// 字节
typedef unsigned char byte;




#endif
