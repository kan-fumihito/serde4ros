#pragma once
#include<iostream>
#include<vector>
#include<cstdint>
#include<string>
#include"PrimitiveSerializer.h"
#include"PrimitiveDeserializer.h"
#include"Time.h"

class Header: public PrimitiveSerializer,PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Header(void);
  void deserialize(std::string &fname);
  void deserialize_Header(void);

  uint32_t seq;
  Time stamp;
  std::string frame_id;
};
