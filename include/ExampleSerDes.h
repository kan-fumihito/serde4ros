#include<iostream>
#include<vector>
#include<cstdint>
#include"PrimitiveSerializer.h"
#include"PrimitiveDerializer.h"
#include"Example.h"

class ExampleSerDes: public PrimitiveSerialize,PrimitiveDeserialize,Example {
public:
  void serialize(std::string &fname);
  void serialize_Example(void);
  void deserialize(std::string &fname);
  void deserialize_Example(void);
}
