#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Deserializer {
public:

  Deserializer(const Deserializer&) = delete;
  Deserializer& operator=(const Deserializer&) = delete;
  Deserializer& operator=(Deserializer&&) = delete;

  Deserializer() = default;
  Deserializer(Deserializer&&) = default;

  bool setInputFile(std::string &fname);
  void closeInputFile(void);

protected:
  std::ifstream ifs_;
};
