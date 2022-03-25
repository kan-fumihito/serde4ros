#pragma once
#include<iostream>
#include<vector>
#include<cstdint>
#include<string>
#include"primitives/PrimitiveSerializer.h"
#include"primitives/PrimitiveDeserializer.h"

class Example: public PrimitiveSerializer,PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Example(void);
  void deserialize(std::string &fname);
  void deserialize_Example(void);

  std::string name;
  std::vector<int32_t> iarray;
  std::vector<float> farray;
};
