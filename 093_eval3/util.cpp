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
  if (trimNum.length() == 0) {
    std::cerr << "no char is a valid number.\n";
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < trimNum.length(); i++) {
    if (!std::isdigit(trimNum[i])) {
      std::cerr << "The story contains invalid number.\n";
      exit(EXIT_FAILURE);
      return false;
    }
  }
  return true;
}

bool checkValidLong(const std::string num) {
  size_t index = 0;
  while (num[index] == ' ') {
    index++;
  }
  if (num[index] == '-' && index != (num.size() - 1)) {
    index++;
  }
  std::string trimNum = num.substr(index);
  if (trimNum.length() == 0) {
    std::cerr << "no char is a valid number.\n";
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < trimNum.length(); i++) {
    if (!std::isdigit(trimNum[i])) {
      std::cerr << "The story contains invalid long number. \n";
      exit(EXIT_FAILURE);
      return false;
    }
  }
  return true;
}
