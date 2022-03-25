#include"HeaderSerDes.h"

void HeaderSerDes::serialize(std::string &fname){
  setFile(fname);
  this->serialize_Header();
}

void HeaderSerDes::serialize_Header(void){

  this->serialize_uint32(this->seq);
  this->serialize_time(this->stamp);
  this->serialize_string(this->frame_id);
}
