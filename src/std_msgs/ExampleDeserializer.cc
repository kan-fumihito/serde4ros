#include"std_msgs/Example.h"

void Example::deserialize(std::string &fname){
  setInputFile(fname);
  this->deserialize_Example();
  closeInputFile();
}

void Example::deserialize_Example(void){

  this->name = this->deserialize_string();
  this->iarray.resize(this->deserialize_uint64());
  for(auto &item:this->iarray){
    item = this->deserialize_int32();
  }
  this->farray.resize(this->deserialize_uint64());
  for(auto &item:this->farray){
    item = this->deserialize_float32();
  }
}
