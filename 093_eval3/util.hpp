#ifndef _UTIL_H__
#define _UTIL_H__
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class UserInputException : public std::exception {
 public:
  const char * what() const throw() {
    return "That is not a valid choice, please try again\n";
  }
};

std::string generatePath(const std::string path, const std::string file);

bool checkValidNum(const std::string num);

#endif
