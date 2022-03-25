#include "Deserializer.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

class PrimitiveDeserializer : public Deserializer {
public:
  uint8_t deserialize_uint8(void);
  int32_t deserialize_int32(void);
  uint32_t deserialize_uint32(void);
  float deserialize_float32(void);
  std::string deserialize_String(void);
  void *deserialize_time(void);
};

uint8_t PrimitiveDeserializer::deserialize_uint8(void) {
  if (!ifs_)
    return 0;

  uint8_t ret;
  ifs_.read((char *)&ret, sizeof(uint8_t));
  return ret;
}

int32_t PrimitiveDeserializer::deserialize_int32(void) {
  if (!ifs_)
    return 0;

  int32_t ret;
  ifs_.read((char *)&ret, sizeof(int32_t));
  return ret;
}

uint32_t PrimitiveDeserializer::deserialize_uint32(void) {
  if (!ifs_)
    return 0;

  uint32_t ret;
  ifs_.read((char *)&ret, sizeof(uint32_t));
  return ret;
}

float PrimitiveDeserializer::deserialize_float32(void) {
  if (!ifs_)
    return 0.0;
  float ret;
  ifs_.read((char *)&ret, sizeof(float));
  return ret;
}

std::string PrimitiveDeserializer::deserialize_String(void) {
  if (!ifs_)
    return "";

  std::string str;
  size_t size;
  ifs_.read((char *)&size, sizeof(size_t));
  auto tmp = std::make_unique<char[]>(size);
  ifs_.read(tmp.get(), size);
  str = std::string(tmp.get());

  return str;
}

void *PrimitiveDeserializer::deserialize_time(void) {
  if (!ifs_)
    return nullptr;
  // unimplemented
}
