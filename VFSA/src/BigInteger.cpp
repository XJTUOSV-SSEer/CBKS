#include "../include/BigInteger.h"
#include <iostream>
#include <cstdio>
#include <cstring>


BigInteger::BigInteger(){
    this->bi=BN_new();
}


BigInteger::BigInteger(std::string s){
    this->bi=BN_new();
    int flag=BN_dec2bn(&(this->bi),s.c_str());
    if(flag==0){
        std::cout<<"convert error"<<std::endl;
    }
}



BigInteger::~BigInteger(){
    BN_clear(this->bi);
}