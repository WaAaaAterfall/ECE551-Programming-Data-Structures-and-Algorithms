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
  int index = 0;
  while (num[index] == ' ') {
    index++;
  }
  std::string trimNum = num.substr(index);
  for (size_t i = 0; i < trimNum.length(); i++) {
    if (!std::isdigit(trimNum[i])) {
      return false;
    }
  }
  return true;
}
