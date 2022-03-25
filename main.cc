#include "std_msgs/Example.h"
#include <iostream>
#include <string>

int main(void) {
  Example ex;
  ex.name = std::string("kan-fumihito");

  for (int i = 0; i < 10; i += 2) {
    ex.iarray.push_back(i);
    std::cout << i << std::endl;
    ex.farray.push_back(i / 0.3);
    std::cout << i / 0.3 << std::endl;
  }

  std::string fname("example.dat");
  ex.serialize(fname);

  Example dex;
  dex.deserialize(fname);

  std::cout << "===deserialized data===" << std::endl;
  std::cout << dex.name << std::endl;
  for (int i = 0; i < dex.iarray.size(); i++) {
    std::cout << dex.iarray[i] << std::endl;
    std::cout << dex.farray[i] << std::endl;
  }

  return 0;
}
