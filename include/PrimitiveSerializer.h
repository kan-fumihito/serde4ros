#pragma once
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
  void serialize_string(std::string &arg);
};
