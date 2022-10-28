#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortLine() {
  std::string s;
  std::vector<std::string> stringLines;
  while (!std::cin.eof()) {
    std::getline(std::cin, s);
    stringLines.push_back(s);
  }
  std::sort(stringLines.begin(), stringLines.end());
  std::vector<std::string>::iterator iterate = stringLines.begin();
  while (iterate != stringLines.end()) {
    std::cout << *iterate << std::endl;
    iterate++;
  }
  stringLines.clear();
}

void sortFile(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream readLine(argv[i]);
    if (readLine.fail()) {
      std::cerr << "Failed to read file" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string s;
    std::vector<std::string> stringLine;
    while (!readLine.eof()) {
      std::getline(readLine, s);
      stringLine.push_back(s);
    }
    std::sort(stringLine.begin(), stringLine.end());
    std::vector<std::string>::iterator iterate = stringLine.begin();
    while (iterate != stringLine.end()) {
      std::cout << *iterate << std::endl;
      iterate++;
    }
    stringLine.clear();
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLine();
  }
  if (argc > 1) {
    sortFile(argc, argv);
  }
  return EXIT_SUCCESS;
}
