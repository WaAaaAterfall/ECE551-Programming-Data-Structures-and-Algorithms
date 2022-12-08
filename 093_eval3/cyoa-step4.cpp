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
  std::vector<Page *> & Pages = story.getPages();
  Page * currentPage = Pages[0];
  while (!currentPage->isWinPage() && !currentPage->isLostPage()) {
    currentPage->printPage();
    std::string inputChoice;
    getline(std::cin, inputChoice);
    size_t destinationPage = 0;
    while (destinationPage == 0) {
      try {
        size_t choiceNum = story.getValidInput(inputChoice, currentPage);
        destinationPage = currentPage->getChoices()[choiceNum - 1]->choiceContent.first;
        currentPage = Pages[destinationPage];
        story.updateStoryVar(currentPage);
        story.updatePageValidChoice(currentPage);
      }
      catch (UserInputException & e) {
        std::cout << e.what();
        getline(std::cin, inputChoice);
      }
      catch (InvalidChoiceException & e) {
        std::cout << e.what();
        // currentPage->printChoices();
        getline(std::cin, inputChoice);
      }
    }
  }
  currentPage->printPage();
  return EXIT_SUCCESS;
}