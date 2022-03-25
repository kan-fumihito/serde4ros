#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Serializer {
public:

  Serializer(const Serializer&) = delete;
  Serializer& operator=(const Serializer&) = delete;
  Serializer& operator=(Serializer&&) = delete;

  Serializer() = default;
  Serializer(Serializer&&) = default;

  bool setOutputFile(std::string &fname);
  void closeOutputFile(void);

protected:
  std::ofstream ofs_;
};
