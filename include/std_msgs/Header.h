#pragma once
#include<iostream>
#include<vector>
#include<cstdint>
#include<string>
#include"primitives/PrimitiveSerializer.h"
#include"primitives/PrimitiveDeserializer.h"
#include"std_msgs/Time.h"

class Header: public PrimitiveSerializer,PrimitiveDeserializer {
public:

  Header(const Header&) = delete;
  Header& operator=(const Header&) = delete;
  Header& operator=(Header&&) = delete;

  Header() = default;
  Header(Header&&) = default;

  void serialize(std::string &fname);
  void serialize_Header(void);
  void deserialize(std::string &fname);
  void deserialize_Header(void);

  uint32_t seq;
  Time stamp;
  std::string frame_id;
};
