#include<iostream>
#include<vector>
#include<cstdint>
#include<string>
#include"PrimitiveSerializer.h"
#include"PrimitiveDeserializer.h"

class Message: public PrimitiveSerializer,PrimitiveDeserializer {
public:
  void serialize(std::string &fname);
  void serialize_Message(void);
  void deserialize(std::string &fname);
  void deserialize_Message(void);

  std::string name;
  std::string message;
};
