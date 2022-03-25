#pragma once
#include "primitives/PrimitiveDeserializer.h"
#include "primitives/PrimitiveSerializer.h"
#include "std_msgs/Time.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Header : public PrimitiveSerializer, PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Header(void);
  void deserialize(std::string &fname);
  void deserialize_Header(void);

  uint32_t seq;
  Time stamp;
  std::string frame_id;
};
