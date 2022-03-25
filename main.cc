#include "serializer.h"
#include "deserializer.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class ROSMsgType final{
    private:
        std::string type_name_;
        std::vector<std::pair<std::string, std::string>> params_;
    public:

};

std::vector<std::pair<std::string, std::string>> Example{
    {"string", "name"}, {"int32[]", "iarray"}, {"float32[]", "farray"}};

std::vector<std::pair<std::string, std::string>> Message{{"string", "name"},
                                                         {"string", "message"}};

std::vector<std::pair<std::string, std::string>> Image{
    {"Header", "header"},   {"uint32", "height"},      {"uint32", "width"},
    {"string", "encoding"}, {"uint8", "is_bigendian"}, {"uint32", "step"},
    {"uint8[]", "data"}};

std::vector<std::pair<std::string, std::string>> Header{
    {"uint32", "seq"}, {"time", "stamp"}, {"string", "frame_id"}};

std::string primitives[] = {"uint8",  "uint8[]",  "int32",   "int32[]",
                            "uint32", "uint32[]", "float32", "float32[]",
                            "string", "time"};

template <class T> bool contain(const std::string &s, const T &v) {
  return s.find(v) != std::string::npos;
}

void generate_serializer(std::string type_name,
                std::vector<std::pair<std::string, std::string>> msg) {
  printf("void serialize_%s(void *arg){\n", type_name.c_str());
  printf("  %s *v = (%s*)arg;\n", type_name.c_str(), type_name.c_str());
  for (auto &p : msg) {
      auto &type = p.first;
      auto &var = p.second;
    if (contain(type, "[]")) {
      printf("  serialize_%s_array((void*)&v->%s);\n", type.substr(0,type.size()-2).c_str(),
                var.c_str());
    } else {
      printf("  serialize_%s((void*)&v->%s);\n", type.c_str(),
             var.c_str());
    }
  }
  printf("}\n");
}

void generate_deserializer(std::string type_name,
                std::vector<std::pair<std::string, std::string>> msg) {
  printf("void deserialize_%s(void *arg){\n", type_name.c_str());
  printf("  %s *v = (%s*)arg;\n", type_name.c_str(), type_name.c_str());
  for (auto &p : msg) {
      auto &type = p.first;
      auto &var = p.second;
    if (contain(type, "[]")) {
      printf("  deserialize_%s_array((void*)v->%s);\n", type.substr(0,type.size()-2).c_str(),
                var.c_str());
    } else {
      printf("  deserialize_%s((void*)v->%s);\n", type.c_str(),
             var.c_str());
    }
  }
  printf("}\n");
}

int main(void) {


  generate_serializer("Example", Example);
  std::cout<<std::endl;
  generate_serializer("Message", Message);
  std::cout<<std::endl;
  generate_serializer("Image", Image);
  std::cout<<std::endl;
  generate_serializer("Header", Header);
  std::cout<<std::endl;

  return 0;
}
