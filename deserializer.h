#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

class Deserializer final {
public:
  bool setFile(std::string &fname);

  void deserializeUint8(uint8_t &arg);
  void deserializeUint8Array(std::vector<uint8_t> &arg);
  void deserializeInt32(int32_t &arg);
  void deserializeInt32Array(std::vector<int32_t> &arg);
  void deserializeUint32(uint32_t &arg);
  void deserializeUint32Array(std::vector<uint32_t> &arg);
  void deserializeFloat32(float &arg);
  void deserializeFloat32Array(std::vector<float> &arg);
  void deserializeString(std::string &arg);
  void deserializeTime(void *arg);

private:
  std::ifstream ifs_;
};

bool Deserializer::setFile(std::string &fname) {
  ifs_.open(fname, std::ios::in | std::ios::binary);
  if (!ifs_) {
    std::cerr << "Failed to open file `" << fname << "`" << std::endl;
    return false;
  }
  return true;
}

void Deserializer::deserializeUint8(uint8_t &arg) {
  if (!ifs_)
    return;

  ifs_.read((char *)&arg, sizeof(uint8_t));
}

void Deserializer::deserializeUint8Array(std::vector<uint8_t> &arg) {
  if (!ifs_)
    return;
  std::vector<uint8_t> &vec = *(std::vector<uint8_t> *)arg;
  size_t size;

  ifs_.read((char *)&size, sizeof(size_t));
  vec.reserve(size);

  for (int i = 0; i < size; i++) {
    ifs_.read((char *)&vec[i], sizeof(uint8_t));
  }
}

void Deserializer::deserializeInt32(int32_t &arg) {
  if (!ifs_)
    return;
  ifs_.read((char *)arg, sizeof(int32_t));
}

void Deserializer::deserializeInt32Array(std::vector<int32_t> &arg) {
  if (!ifs_)
    return;

  std::vector<int32_t> &vec = *(std::vector<int32_t> *)arg;
  size_t size;

  ifs_.read((char *)&size, sizeof(size_t));
  vec.reserve(size);

  for (int i = 0; i < size; i++) {
    ifs_.read((char *)&vec[i], sizeof(int32_t));
  }
}

void Deserializer::deserializeUint32(uint32_t &arg) {
  if (!ifs_)
    return;
  ifs_.read((char *)arg, sizeof(uint32_t));
}

void Deserializer::deserializeUint32Array(std::vector<uint32_t> &arg) {
  if (!ifs_)
    return;
  std::vector<uint32_t> &vec = *(std::vector<uint32_t> *)arg;
  size_t size;

  ifs_.read((char *)&size, sizeof(size_t));
  vec.reserve(size);

  for (int i = 0; i < size; i++) {
    ifs_.read((char *)&vec[i], sizeof(uint32_t));
  }
}

void Deserializer::deserializeFloat32(float &arg) {
  if (!ifs_)
    return;
  ifs_.read((char *)arg, sizeof(float));
}

void Deserializer::deserializeFloat32Array(std::vector<float> &arg) {
  if (!ifs_)
    return;
  std::vector<float> &vec = *(std::vector<float> *)arg;
  size_t size;

  ifs_.read((char *)&size, sizeof(size_t));
  vec.reserve(size);

  for (int i = 0; i < size; i++) {
    ifs_.read((char *)&vec[i], sizeof(float));
  }
}

void Deserializer::deserializeString(std::string &arg) {
  if (!ifs_)
    return;
  std::string &str = *(std::string *)arg;
  size_t size;
  ifs_.read((char *)&size, sizeof(size_t));
  char *tmp = new char[size];
  ifs_.read(tmp, size);
  str = std::string(tmp);
  delete[] tmp;
}

void Deserializer::deserializeTime(void *arg) {
  if (!ifs_)
    return;
  // unimplemented
}
