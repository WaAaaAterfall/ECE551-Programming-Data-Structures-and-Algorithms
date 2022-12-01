#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "Story.hpp"
#include "util.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong input!\n";
    return EXIT_FAILURE;
  }
  std::string path = argv[1];
  Story story(path);
  story.checkStory();
  story.searchSuccessPath();
  story.printSuccessPath();
  return EXIT_SUCCESS;
}
