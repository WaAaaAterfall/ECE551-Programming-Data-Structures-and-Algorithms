#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "Page.hpp"
#include "Story.hpp"
#include "util.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong input!\n";
    return EXIT_FAILURE;
  }
  std::string path = argv[1];
  Story story(path);
  story.checkStoryFormat();
  story.printStory();

  // std::string input = "0@N:page0.txt\n";
  // Page testPage(input.substr(0, input.size() - 1));
  // std::cout << input.substr(0, input.size() - 1);
  // std::cout << testPage.getPageNum();
  // std::cout << testPage.getPageType();
  // testPage.printPage();
  // testPage.addChoices("2:Choose the magic whistle.\n");
  // testPage.addChoices("3:Choose the magic shoes.\n");
  // testPage.addChoices("4:Choose the magic toaster.\n");
  //  testPage.printPage();
}
