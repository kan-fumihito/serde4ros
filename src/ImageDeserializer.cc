#include"Image.h"

void Image::deserialize(std::string &fname){
  setInputFile(fname);
  this->deserialize_Image();
}

void Image::deserialize_Image(void){

  this->header.deserialize_Header();
  this->height = this->deserialize_uint32();
  this->width = this->deserialize_uint32();
  this->encoding = this->deserialize_string();
  this->is_bigendian = this->deserialize_uint8();
  this->step = this->deserialize_uint32();
  for(auto &item:this->data){
    item = this->deserialize_uint8();
  }
}
