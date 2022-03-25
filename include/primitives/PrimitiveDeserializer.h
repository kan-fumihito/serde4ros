#pragma once
#include "Deserializer.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

class PrimitiveDeserializer : public Deserializer {
public:

  PrimitiveDeserializer(const PrimitiveDeserializer&) = delete;
  PrimitiveDeserializer& operator=(const PrimitiveDeserializer&) = delete;
  PrimitiveDeserializer& operator=(PrimitiveDeserializer&&) = delete;
  
  PrimitiveDeserializer() = default;
  PrimitiveDeserializer(PrimitiveDeserializer&&) = default;

  uint8_t deserialize_uint8(void);
  int32_t deserialize_int32(void);
  uint32_t deserialize_uint32(void);
  uint64_t deserialize_uint64(void);
  float deserialize_float32(void);
  std::string deserialize_string(void);
};
