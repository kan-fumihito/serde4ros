#include"MessageSerDes.h"

void MessageSerDes::serialize(std::string &fname){
  setFile(fname);
  this->serialize_Message();
}

void MessageSerDes::serialize_Message(void){

  this->serialize_string(this->name);
  this->serialize_string(this->message);
}
