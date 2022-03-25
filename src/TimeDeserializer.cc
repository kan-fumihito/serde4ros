#include"Time.h"

void Time::deserialize(std::string &fname){
  setInputFile(fname);
  this->deserialize_Time();
}

void Time::deserialize_Time(void){

  this->time = this->deserialize_uint32();
}
