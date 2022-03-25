#include"std_msgs/Time.h"

void Time::serialize(std::string &fname){
  setOutputFile(fname);
  this->serialize_Time();
  closeOutputFile();
}

void Time::serialize_Time(void){

  this->serialize_uint32(this->time);
}
