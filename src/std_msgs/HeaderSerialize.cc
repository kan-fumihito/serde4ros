#include"std_msgs/Header.h"

void Header::serialize(std::string &fname){
  setOutputFile(fname);
  this->serialize_Header();
  closeOutputFile();
}

void Header::serialize_Header(void){

  this->serialize_uint32(this->seq);
  this->stamp.serialize_Time();
  this->serialize_string(this->frame_id);
}
