#include"Header.h"

void Header::deserialize(std::string &fname){
  setInputFile(fname);
  this->deserialize_Header();
}

void Header::deserialize_Header(void){

  this->seq = this->deserialize_uint32();
  this->stamp.deserialize_Time();
  this->frame_id = this->deserialize_string();
}
