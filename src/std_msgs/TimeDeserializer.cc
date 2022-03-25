#include"std_msgs/Time.h"

void Time::deserialize(std::string &fname){
  setInputFile(fname);
  this->deserialize_Time();
  closeInputFile();
}

void Time::deserialize_Time(void){

  this->time = this->deserialize_uint32();
}
