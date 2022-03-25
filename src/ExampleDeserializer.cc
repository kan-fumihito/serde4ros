#include"Example.h"

void Example::deserialize(std::string &fname){
  setInputFile(fname);
  this->deserialize_Example();
}

void Example::deserialize_Example(void){

  this->name = this->deserialize_string();
  for(auto &item:this->iarray){
    item = this->deserialize_int32();
  }
  for(auto &item:this->farray){
    item = this->deserialize_float32();
  }
}
