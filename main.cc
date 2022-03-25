#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

class ROSMsgType final {
public:
  ROSMsgType(std::string type_name,
             std::vector<std::pair<std::string, std::string>> params)
      : type_name_(type_name), params_(params){};

  const std::string &getTypeName(void) const { return type_name_; };
  const std::vector<std::pair<std::string, std::string>> &
  getParams(void) const {
    return params_;
  };

private:
  std::string type_name_;
  std::vector<std::pair<std::string, std::string>> params_;
};

const std::vector<std::pair<std::string, std::string>> Example{
    {"string", "name"}, {"int32[]", "iarray"}, {"float32[]", "farray"}};

const std::vector<std::pair<std::string, std::string>> Message{
    {"string", "name"}, {"string", "message"}};

const std::vector<std::pair<std::string, std::string>> Image{
    {"Header", "header"},   {"uint32", "height"},      {"uint32", "width"},
    {"string", "encoding"}, {"uint8", "is_bigendian"}, {"uint32", "step"},
    {"uint8[]", "data"}};

const std::vector<std::pair<std::string, std::string>> Header{
    {"uint32", "seq"}, {"time", "stamp"}, {"string", "frame_id"}};

const std::vector<std::string> primitiveTypes = {"uint8",   "int32",  "uint32",
                                                 "float32", "string", "time"};

const std::map<std::string, std::string> primitiveTypeMap = {
    {"uint8", "uint8_t"}, {"int32", "int32_t"},      {"uint32", "uint32_t"},
    {"float32", "float"}, {"string", "std::string"}, {"time", "time"}};

const std::vector<ROSMsgType> msgTypes{
    ROSMsgType("Example", Example), ROSMsgType("Message", Message),
    ROSMsgType("Image", Image), ROSMsgType("Header", Header)};

template <class T> bool contain(const std::string &s, const T &v) {
  return s.find(v) != std::string::npos;
}

void generate_header(const ROSMsgType &msg) {
  FILE *fp;
  {
    auto t = msg.getTypeName();
    fp = fopen(std::string("include/"+t + "SerDes.h").c_str(), "w");
    fprintf(fp, "#include<iostream>\n");
    fprintf(fp, "#include<vector>\n");
    fprintf(fp, "#include<cstdint>\n");
    fprintf(fp, "#include\"PrimitiveSerializer.h\"\n");
    fprintf(fp, "#include\"PrimitiveDerializer.h\"\n");
    fprintf(fp, "#include\"%s.h\"\n", t.c_str());
  }
  fprintf(fp, "\n");
  std::string head("class " + msg.getTypeName() + "SerDes" +
                   ": public PrimitiveSerialize,PrimitiveDeserialize," +
                   msg.getTypeName() + " {\n");

  std::vector<std::string> public_rows, private_rows;
  public_rows.emplace_back("public:\n");
  public_rows.emplace_back("  void serialize(std::string &fname);\n");
  public_rows.emplace_back("  void serialize_" + msg.getTypeName() +
                           "(void);\n");
  public_rows.emplace_back("  void deserialize(std::string &fname);\n");
  public_rows.emplace_back("  void deserialize_" + msg.getTypeName() +
                           "(void);\n");

  std::string tail("}\n");

  fprintf(fp, "%s", head.c_str());
  for (auto &item : public_rows) {
    fprintf(fp, "%s", item.c_str());
  }
  for (auto &item : private_rows) {
    fprintf(fp, "%s", item.c_str());
  }
  fprintf(fp, "%s", tail.c_str());
}

void generate_serializer(const ROSMsgType &msg) {
  FILE *fp;
  {
    auto t = msg.getTypeName();
    fp = fopen(std::string("src/"+t + "Serialize.cc").c_str(), "w");
    fprintf(fp, "#include\"%sSerDes.h\"\n\n", t.c_str());
    fprintf(fp, "void %sSerDes::serialize(std::string &fname){\n", t.c_str());
    fprintf(fp, "  setFile(fname);\n");
    fprintf(fp, "  this->serialize_%s();\n", t.c_str());
    fprintf(fp, "}\n\n");
    fprintf(fp, "void %sSerDes::serialize_%s(void){\n", t.c_str(), t.c_str());
  }
  fprintf(fp, "\n");

  for (const auto &p : msg.getParams()) {

    if (contain(p.first, "[]")) {
      //配列
      auto t = p.first.substr(0, p.first.size() - 2);
      fprintf(fp, "  for(auto &item:this->%s){\n", p.second.c_str());
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), t) !=
          primitiveTypes.end()) {
        //プリミティブ型
        fprintf(fp, "    this->serialize_%s(item);\n", t.c_str());
      } else {
        //ユーザ定義型
        fprintf(fp, "    ((%sSerDes*)&item)->serialize_%s();\n", t.c_str(),
                t.c_str());
      }
      fprintf(fp, "  }\n");
    } else {
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), p.first) !=
          primitiveTypes.end()) {
        //プリミティブ型
        fprintf(fp, "  this->serialize_%s(this->%s);\n", p.first.c_str(),
                p.second.c_str());
      } else {
        //ユーザ定義型
        fprintf(fp, "  ((%sSerDes*)&this->%s)->serialize_%s();\n",
                p.first.c_str(), p.second.c_str(), p.first.c_str());
      }
    }
  }
  fprintf(fp, "}\n");
}

void generate_deserializer(const ROSMsgType &msg) {
  FILE *fp;
  {
    auto t = msg.getTypeName();
    fp = fopen(std::string(t + "Deserializer.cc").c_str(), "w");
    fprintf(fp, "#include\"%sSerDes.h\"\n\n", t.c_str());
    fprintf(fp, "void %sSerDes::deserialize(std::string &fname){\n", t.c_str());
    fprintf(fp, "  setFile(fname);\n");
    fprintf(fp, "  this->deserialize_%s();\n", t.c_str());
    fprintf(fp, "}\n\n");
    fprintf(fp, "void %sSerDes::deserialize_%s(void){\n", t.c_str(), t.c_str());
  }
  fprintf(fp, "\n");
  for (const auto &p : msg.getParams()) {

    if (contain(p.first, "[]")) {
      //配列
      auto t = p.first.substr(0, p.first.size() - 2);
      fprintf(fp, "  for(auto &item:this->%s){\n", p.second.c_str());
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), t) !=
          primitiveTypes.end()) {
        //プリミティブ型
        fprintf(fp, "    item = this->deserialize_%s();\n", t.c_str());
      } else {
        //ユーザ定義型
        fprintf(fp, "    ((%sSerDes*)&item)->deserialize_%s();\n", t.c_str(),
                t.c_str());
      }
      fprintf(fp, "  }\n");
    } else {
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), p.first) !=
          primitiveTypes.end()) {
        //プリミティブ型
        fprintf(fp, "  this->%s = this->deserialize_%s();\n", p.second.c_str(),
                p.first.c_str());
      } else {
        //ユーザ定義型
        fprintf(fp, "  ((%sSerDes*)&this->%s)->deserialize_%s();\n",
                p.first.c_str(), p.second.c_str(), p.first.c_str());
      }
    }
  }
  fprintf(fp, "}\n");
}

int main(void) {

  for (auto &msgType : msgTypes) {
    generate_header(msgType);
    generate_serializer(msgType);
    generate_deserializer(msgType);
  }

  return 0;
}
