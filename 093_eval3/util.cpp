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
