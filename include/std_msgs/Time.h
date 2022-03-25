#pragma once
#include<iostream>
#include<vector>
#include<cstdint>
#include<string>
#include"primitives/PrimitiveSerializer.h"
#include"primitives/PrimitiveDeserializer.h"

class Time: public PrimitiveSerializer,PrimitiveDeserializer {
public:

  Time(const Time&) = delete;
  Time& operator=(const Time&) = delete;
  Time& operator=(Time&&) = delete;

  Time() = default;
  Time(Time&&) = default;

  void serialize(std::string &fname);
  void serialize_Time(void);
  void deserialize(std::string &fname);
  void deserialize_Time(void);

  uint32_t time;
};
