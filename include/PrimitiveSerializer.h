#include "Serializer.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

class PrimitiveSerializer : public Serializer {
public:
  void serialize_uint8(uint8_t &arg);
  void serialize_int32(int32_t &arg);
  void serialize_uint32(uint32_t &arg);
  void serialize_float32(float &arg);
  void serialize_String(std::string &arg);
  void serialize_time(void *arg);
};

void PrimitiveSerializer::serialize_uint8(uint8_t &arg) {
  if (!ofs_)
    return;

  ofs_.write((char *)&arg, sizeof(uint8_t));
}

void PrimitiveSerializer::serialize_int32(int32_t &arg) {
  if (!ofs_)
    return;

  ofs_.write((char *)&arg, sizeof(int32_t));
}

void PrimitiveSerializer::serialize_uint32(uint32_t &arg) {
  if (!ofs_)
    return;
  ofs_.write((char *)&arg, sizeof(uint32_t));
}

void PrimitiveSerializer::serialize_float32(float &arg) {
  if (!ofs_)
    return;

  ofs_.write((char *)&arg, sizeof(float));
}

void PrimitiveSerializer::serialize_String(std::string &arg) {
  if (!ofs_)
    return;

  size_t size = arg.size();
  ofs_.write((char *)&size, sizeof(size_t));
  ofs_.write(arg.c_str(), size);
}

void PrimitiveSerializer::serialize_time(void *arg) {
  if (!ofs_)
    return;
  // unimplemented
}
