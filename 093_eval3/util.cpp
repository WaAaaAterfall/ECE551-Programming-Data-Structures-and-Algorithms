#include "util.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string generatePath(const std::string path, const std::string file) {
  std::ostringstream fileName;
  fileName << path << "/" << file;
  std::string filePath = fileName.str();
  return filePath;
}

bool checkValidNum(const std::string num) {
  for (size_t i = 0; i < num.length(); i++) {
    if (!std::isdigit(num[i])) {
      return false;
    }
  }
  return true;
}
