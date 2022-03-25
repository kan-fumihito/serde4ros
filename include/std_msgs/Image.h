#pragma once
#include "primitives/PrimitiveDeserializer.h"
#include "primitives/PrimitiveSerializer.h"
#include "std_msgs/Header.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Image : public PrimitiveSerializer, PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Image(void);
  void deserialize(std::string &fname);
  void deserialize_Image(void);

  Header header;
  uint32_t height;
  uint32_t width;
  std::string encoding;
  uint8_t is_bigendian;
  uint32_t step;
  std::vector<uint8_t> data;
};
