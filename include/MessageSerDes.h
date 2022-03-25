#include<iostream>
#include<vector>
#include<cstdint>
#include"PrimitiveSerializer.h"
#include"PrimitiveDerializer.h"
#include"Message.h"

class MessageSerDes: public PrimitiveSerialize,PrimitiveDeserialize,Message {
public:
  void serialize(std::string &fname);
  void serialize_Message(void);
  void deserialize(std::string &fname);
  void deserialize_Message(void);
}
