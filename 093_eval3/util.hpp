#ifndef _UTIL_H__
#define _UTIL_H__
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class EmptyInputException : public std::exception {
 public:
  const char * what() const throw() { return "That choice is empty, please try again\n"; }
};

class UserInputException : public std::exception {
 public:
  const char * what() const throw() {
    return "That is not a valid choice, please try again\n";
  }
};

class InvalidChoiceException : public std::exception {
 public:
  const char * what() const throw() {
    return "That choice is not available at this time, please try again\n";
  }
};

std::string generatePath(const std::string path, const std::string file);

bool checkValidInputNum(const std::string num);

bool checkValidNum(const std::string num);

bool checkValidLong(const std::string num);

#endif
