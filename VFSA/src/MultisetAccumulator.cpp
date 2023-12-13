#include<iostream>
#include "../include/MultisetAccumulator.h"
#include "../include/BigInteger.h"

#define P_BITS_LEN 128      // 素数P的位数
#define Q_BITS_LEN 128      // 素数Q的位数


MultisetAccumulator::MultisetAccumulator(){
    // 生成P,Q
    BigInteger p,q;
    BigInteger::generate_prime(p,P_BITS_LEN,1);
    BigInteger::generate_prime(q,Q_BITS_LEN,1);

    P=p.to_string();
    Q=q.to_string();

    // 生成N=PQ
    BigInteger n;
    BigInteger::mul(n,p,q);
    N=n.to_string();

    // g=65537
    g=65537;


    std::cout<<P<<std::endl<<Q<<std::endl<<N<<std::endl;

}
