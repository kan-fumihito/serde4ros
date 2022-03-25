#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

// msgファイルの情報を以下のクラスに落とし込む実装はしていない
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

//　msgファイルの情報をパースせずにハードコードしたものをいくつか用意
// Example.msg
const std::vector<std::pair<std::string, std::string>> Example{
    {"string", "name"}, {"int32[]", "iarray"}, {"float32[]", "farray"}};

const std::vector<std::pair<std::string, std::string>> Message{
    {"string", "name"}, {"string", "message"}};

const std::vector<std::pair<std::string, std::string>> Image{
    {"Header", "header"},   {"uint32", "height"},      {"uint32", "width"},
    {"string", "encoding"}, {"uint8", "is_bigendian"}, {"uint32", "step"},
    {"uint8[]", "data"}};

const std::vector<std::pair<std::string, std::string>> Header{
    {"uint32", "seq"}, {"Time", "stamp"}, {"string", "frame_id"}};

const std::vector<std::pair<std::string, std::string>> Time{{"uint32", "time"}};

// msgファイルのサンプル
const std::vector<ROSMsgType> msgTypes{
    ROSMsgType("Example", Example), ROSMsgType("Message", Message),
    ROSMsgType("Image", Image), ROSMsgType("Header", Header),
    ROSMsgType("Time", Time)};

// msgファイル内で使われるプリミティブ型のエイリアス
const std::vector<std::string> primitiveTypes = {"uint8",  "int32",   "uint32",
                                                 "uint64", "float32", "string"};

// msgファイルのプリミティブ型エイリアスと、C++での型エイリアスの対応表
const std::map<std::string, std::string> primitiveTypeMap = {
    {"uint8", "uint8_t"},   {"int32", "int32_t"}, {"uint32", "uint32_t"},
    {"uint64", "uint64_t"}, {"float32", "float"}, {"string", "std::string"}};

template <class T> bool contain(const std::string &s, const T &v) {
  return s.find(v) != std::string::npos;
}

// ヘッダファイル生成
void generate_header(const ROSMsgType &msg) {
  FILE *fp;
  {
    auto t = msg.getTypeName();
    fp = fopen(std::string("include/std_msgs/" + t + ".h").c_str(), "w");
    fprintf(fp, "#pragma once\n");
    fprintf(fp, "#include<iostream>\n");
    fprintf(fp, "#include<vector>\n");
    fprintf(fp, "#include<cstdint>\n");
    fprintf(fp, "#include<string>\n");
    fprintf(fp, "#include\"primitives/PrimitiveSerializer.h\"\n");
    fprintf(fp, "#include\"primitives/PrimitiveDeserializer.h\"\n");
  }

  std::string head("class " + msg.getTypeName() +
                   ": public PrimitiveSerializer,PrimitiveDeserializer" +
                   " {\n");

  std::vector<std::string> public_rows, private_rows;
  public_rows.emplace_back("public:\n");
  public_rows.emplace_back("  void serialize(std::string &fname);\n");
  public_rows.emplace_back("  void serialize_" + msg.getTypeName() +
                           "(void);\n");
  public_rows.emplace_back("  void deserialize(std::string &fname);\n");
  public_rows.emplace_back("  void deserialize_" + msg.getTypeName() +
                           "(void);\n");

  public_rows.emplace_back("\n");
  for (auto &p : msg.getParams()) {
    if (contain(p.first, "[]")) {
      //配列
      auto t = p.first.substr(0, p.first.size() - 2);
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), t) !=
          primitiveTypes.end()) {
        //プリミティブ型
        public_rows.emplace_back("  std::vector<" + primitiveTypeMap.at(t) +
                                 "> " + p.second + ";\n");
      } else {
        //ユーザ定義型
        fprintf(fp, "#include\"std_msgs/%s.h\"\n", t.c_str());
        public_rows.emplace_back("  std::vector<" + t + "> " + p.second +
                                 ";\n");
      }
    } else {
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), p.first) !=
          primitiveTypes.end()) {
        //プリミティブ型
        public_rows.emplace_back("  " + primitiveTypeMap.at(p.first) + " " +
                                 p.second + ";\n");
      } else {
        //ユーザ定義型
        fprintf(fp, "#include\"std_msgs/%s.h\"\n", p.first.c_str());
        public_rows.emplace_back("  " + p.first + " " + p.second + ";\n");
      }
    }
  }
  std::string tail("};\n");

  fprintf(fp, "\n");
  fprintf(fp, "%s", head.c_str());
  for (auto &item : public_rows) {
    fprintf(fp, "%s", item.c_str());
  }
  for (auto &item : private_rows) {
    fprintf(fp, "%s", item.c_str());
  }
  fprintf(fp, "%s", tail.c_str());
}

// シリアライズクラス生成
void generate_serializer(const ROSMsgType &msg) {
  FILE *fp;
  {
    auto t = msg.getTypeName();
    fp = fopen(std::string("src/std_msgs/" + t + "Serialize.cc").c_str(), "w");
    fprintf(fp, "#include\"std_msgs/%s.h\"\n\n", t.c_str());
    fprintf(fp, "void %s::serialize(std::string &fname){\n", t.c_str());
    fprintf(fp, "  setOutputFile(fname);\n");
    fprintf(fp, "  this->serialize_%s();\n", t.c_str());
    fprintf(fp, "  closeOutputFile();\n");
    fprintf(fp, "}\n\n");
    fprintf(fp, "void %s::serialize_%s(void){\n", t.c_str(), t.c_str());
  }
  fprintf(fp, "\n");

  for (const auto &p : msg.getParams()) {

    if (contain(p.first, "[]")) {
      //配列
      auto t = p.first.substr(0, p.first.size() - 2);
      fprintf(fp, "  this->serialize_uint64(this->%s.size());\n",
              p.second.c_str());
      fprintf(fp, "  for(auto &item:this->%s){\n", p.second.c_str());
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), t) !=
          primitiveTypes.end()) {
        //プリミティブ型
        fprintf(fp, "    this->serialize_%s(item);\n", t.c_str());
      } else {
        //ユーザ定義型
        fprintf(fp, "    item.serialize_%s();\n", t.c_str());
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
        fprintf(fp, "  this->%s.serialize_%s();\n", p.second.c_str(),
                p.first.c_str());
      }
    }
  }
  fprintf(fp, "}\n");
}

// デシリアライズクラス生成
void generate_deserializer(const ROSMsgType &msg) {
  FILE *fp;
  {
    auto t = msg.getTypeName();
    fp = fopen(std::string("src/std_msgs/" + t + "Deserializer.cc").c_str(),
               "w");
    fprintf(fp, "#include\"std_msgs/%s.h\"\n\n", t.c_str());
    fprintf(fp, "void %s::deserialize(std::string &fname){\n", t.c_str());
    fprintf(fp, "  setInputFile(fname);\n");
    fprintf(fp, "  this->deserialize_%s();\n", t.c_str());
    fprintf(fp, "  closeInputFile();\n");
    fprintf(fp, "}\n\n");
    fprintf(fp, "void %s::deserialize_%s(void){\n", t.c_str(), t.c_str());
  }
  fprintf(fp, "\n");
  for (const auto &p : msg.getParams()) {

    if (contain(p.first, "[]")) {
      //配列
      auto t = p.first.substr(0, p.first.size() - 2);
      fprintf(fp, "  this->%s.resize(this->deserialize_uint64());\n",
              p.second.c_str());
      fprintf(fp, "  for(auto &item:this->%s){\n", p.second.c_str());
      if (std::find(primitiveTypes.begin(), primitiveTypes.end(), t) !=
          primitiveTypes.end()) {
        //プリミティブ型
        fprintf(fp, "    item = this->deserialize_%s();\n", t.c_str());
      } else {
        //ユーザ定義型
        fprintf(fp, "    item.deserialize_%s();\n", t.c_str());
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
        fprintf(fp, "  this->%s.deserialize_%s();\n", p.second.c_str(),
                p.first.c_str());
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
