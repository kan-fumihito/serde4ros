#include"std_msgs/Message.h"

void Message::deserialize(std::string &fname){
  setInputFile(fname);
  this->deserialize_Message();
  closeInputFile();
}

void Message::deserialize_Message(void){

  this->name = this->deserialize_string();
  this->message = this->deserialize_string();
}
