#include<iostream>
#include<string>
#include"Example.h"

int main(void){
    Example ex;
    ex.name=std::string("kan-fumihito");
    
    for(int i=0;i<100;i+=2){
        ex.iarray.push_back(i);
        ex.farray.push_back(i/0.3);
    }


    std::string fname("example.dat");
    ex.serialize(fname);

    return 0;
}
