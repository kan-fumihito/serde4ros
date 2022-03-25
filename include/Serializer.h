#include <fstream>
#include <iostream>
#include <string>

class Serializer {
public:
  bool setOutputFile(std::string &fname);

protected:
  std::ofstream ofs_;
};

bool Serializer::setOutputFile(std::string &fname) {
  ofs_.open(fname, std::ios::out | std::ios::binary);
  if (!ofs_) {
    std::cerr << "Failed to open file `" << fname << "`" << std::endl;
    return false;
  }
  return true;
}
