#pragma once
#include<iostream>
#include<vector>
#include<cstdint>
#include<string>
#include"primitives/PrimitiveSerializer.h"
#include"primitives/PrimitiveDeserializer.h"
#include"std_msgs/Header.h"

class Image: public PrimitiveSerializer,PrimitiveDeserializer {
public:

  Image(const Image&) = delete;
  Image& operator=(const Image&) = delete;
  Image& operator=(Image&&) = delete;

  Image() = default;
  Image(Image&&) = default;

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
