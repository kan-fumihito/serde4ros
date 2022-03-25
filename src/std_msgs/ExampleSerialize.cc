#include "std_msgs/Example.h"

void Example::serialize(std::string &fname) {
  setOutputFile(fname);
  this->serialize_Example();
  closeOutputFile();
}

void Example::serialize_Example(void) {

  this->serialize_string(this->name);
  this->serialize_uint64(this->iarray.size());
  for (auto &item : this->iarray) {
    this->serialize_int32(item);
  }
  this->serialize_uint64(this->farray.size());
  for (auto &item : this->farray) {
    this->serialize_float32(item);
  }
}
