#pragma once
#include "primitives/PrimitiveDeserializer.h"
#include "primitives/PrimitiveSerializer.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Message : public PrimitiveSerializer, PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Message(void);
  void deserialize(std::string &fname);
  void deserialize_Message(void);

  std::string name;
  std::string message;
};
