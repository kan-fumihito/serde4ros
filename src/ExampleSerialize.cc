#include"Example.h"

void Example::serialize(std::string &fname){
  setOutputFile(fname);
  this->serialize_Example();
}

void Example::serialize_Example(void){

  this->serialize_string(this->name);
  for(auto &item:this->iarray){
    this->serialize_int32(item);
  }
  for(auto &item:this->farray){
    this->serialize_float32(item);
  }
}
