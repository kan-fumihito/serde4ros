#include <fstream>
#include <iostream>
#include <string>

class Deserializer {
public:
  bool setFile(std::string &fname);

protected:
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
