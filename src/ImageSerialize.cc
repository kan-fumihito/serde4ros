#include"Image.h"

void Image::serialize(std::string &fname){
  setOutputFile(fname);
  this->serialize_Image();
}

void Image::serialize_Image(void){

  this->header.serialize_Header();
  this->serialize_uint32(this->height);
  this->serialize_uint32(this->width);
  this->serialize_string(this->encoding);
  this->serialize_uint8(this->is_bigendian);
  this->serialize_uint32(this->step);
  for(auto &item:this->data){
    this->serialize_uint8(item);
  }
}
