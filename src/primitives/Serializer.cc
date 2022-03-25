#include "primitives/Serializer.h"
#include <fstream>
#include <iostream>
#include <string>

bool Serializer::setOutputFile(std::string &fname) {
  ofs_.open(fname, std::ios::out | std::ios::binary);
  if (!ofs_) {
    std::cerr << "Failed to open file `" << fname << "`" << std::endl;
    return false;
  }
  return true;
}

void Serializer::closeOutputFile(void) { ofs_.close(); }
