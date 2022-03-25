#pragma once
#include "primitives/PrimitiveDeserializer.h"
#include "primitives/PrimitiveSerializer.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Example : public PrimitiveSerializer, PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Example(void);
  void deserialize(std::string &fname);
  void deserialize_Example(void);

  std::string name;
  std::vector<int32_t> iarray;
  std::vector<float> farray;
};
