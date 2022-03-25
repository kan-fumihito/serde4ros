#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Serializer {
public:
  bool setOutputFile(std::string &fname);

protected:
  std::ofstream ofs_;
};
