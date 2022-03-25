#include<iostream>
#include<vector>
#include<cstdint>
#include"PrimitiveSerializer.h"
#include"PrimitiveDerializer.h"
#include"Image.h"

class ImageSerDes: public PrimitiveSerialize,PrimitiveDeserialize,Image {
public:
  void serialize(std::string &fname);
  void serialize_Image(void);
  void deserialize(std::string &fname);
  void deserialize_Image(void);
}
