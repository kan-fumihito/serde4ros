#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

class Serializer final {
public:
  bool setFile(std::string &fname);

  void serializeUint8(uint8_t &arg);
  void serializeUint8Array(std::vector<uint8_t> &arg);
  void serializeInt32(int32_t &arg);
  void serializeInt32Array(std::vector<int32_t> &arg);
  void serializeUint32(uint32_t &arg);
  void serializeUint32Array(std::vector<uint32_t> &arg);
  void serializeFloat32(float &arg);
  void serializeFloat32Array(std::vector<float> &arg);
  void serializeString(std::string &arg);
  void serializeTime(void *arg);

private:
  std::ofstream ofs_;
};

bool Serializer::setFile(std::string &fname) {
  ofs_.open(fname, std::ios::out | std::ios::binary);
  if (!ofs_) {
    std::cerr << "Failed to open file `" << fname << "`" << std::endl;
    return false;
  }
  return true;
}

void Serializer::serializeUint8(uint8_t &arg) {
  if (!ofs_)
    return;

  ofs_.write((char *)&arg, sizeof(uint8_t));
}

void Serializer::serializeUint8Array(std::vector<uint8_t> &arg) {
  if (!ofs_)
    return;

  size_t size = arg.size();
  ofs_.write((char *)&size, sizeof(size_t));
  for (auto item : arg) {
    ofs_.write((char *)&item, sizeof(uint8_t));
  }
}

void Serializer::serializeInt32(int32_t &arg) {
  if (!ofs_)
    return;

  ofs_.write((char *)&arg, sizeof(int32_t));
}

void Serializer::serializeInt32Array(std::vector<int32_t> &arg) {
  if (!ofs_)
    return;

  size_t size = arg.size();
  ofs_.write((char *)&size, sizeof(size_t));
  for (auto item : arg) {
    ofs_.write((char *)&item, sizeof(int32_t));
  }
}

void Serializer::serializeUint32(uint32_t &arg) {
  if (!ofs_)
    return;
  ofs_.write((char *)&arg, sizeof(uint32_t));
}

void Serializer::serializeUint32Array(std::vector<uint32_t> &arg) {
  if (!ofs_)
    return;

  size_t size = arg.size();
  ofs_.write((char *)&size, sizeof(size_t));
  for (auto item : arg) {
    ofs_.write((char *)&item, sizeof(uint32_t));
  }
}

void Serializer::serializeFloat32(float &arg) {
  if (!ofs_)
    return;

  ofs_.write((char *)&arg, sizeof(float));
}

void Serializer::serializeFloat32Array(std::vector<float> &arg) {
  if (!ofs_)
    return;
    
  size_t size = arg.size();
  ofs_.write((char *)&size, sizeof(size_t));
  for (auto item : arg) {
    ofs_.write((char *)&item, sizeof(float));
  }
}

void Serializer::serializeString(std::string &arg) {
  if (!ofs_)
    return;

  size_t size = arg.size();
  ofs_.write((char *)&size, sizeof(size_t));
  ofs_.write(arg.c_str(), size);
}

void Serializer::serializeTime(void *arg) {
  if (!ofs_)
    return;
  // unimplemented
}
