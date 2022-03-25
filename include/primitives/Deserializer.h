#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Deserializer {
public:
  bool setInputFile(std::string &fname);
  void closeInputFile(void);

protected:
  std::ifstream ifs_;
};
