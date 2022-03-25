#pragma once
#include "primitives/PrimitiveDeserializer.h"
#include "primitives/PrimitiveSerializer.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Time : public PrimitiveSerializer, PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Time(void);
  void deserialize(std::string &fname);
  void deserialize_Time(void);

  uint32_t time;
};
