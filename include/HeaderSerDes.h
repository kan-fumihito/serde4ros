#include<iostream>
#include<vector>
#include<cstdint>
#include"PrimitiveSerializer.h"
#include"PrimitiveDerializer.h"
#include"Header.h"

class HeaderSerDes: public PrimitiveSerialize,PrimitiveDeserialize,Header {
public:
  void serialize(std::string &fname);
  void serialize_Header(void);
  void deserialize(std::string &fname);
  void deserialize_Header(void);
}
