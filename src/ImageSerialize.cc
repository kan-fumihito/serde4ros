#include"ImageSerDes.h"

void ImageSerDes::serialize(std::string &fname){
  setFile(fname);
  this->serialize_Image();
}

void ImageSerDes::serialize_Image(void){

  ((HeaderSerDes*)&this->header)->serialize_Header();
  this->serialize_uint32(this->height);
  this->serialize_uint32(this->width);
  this->serialize_string(this->encoding);
  this->serialize_uint8(this->is_bigendian);
  this->serialize_uint32(this->step);
  for(auto &item:this->data){
    this->serialize_uint8(item);
  }
}
