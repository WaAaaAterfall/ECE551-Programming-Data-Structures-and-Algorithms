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
  Story * storyTestRF3 = new Story(path);
  Story story(*storyTestRF3);
  delete storyTestRF3;
  story.checkStory();

  std::vector<Page *> Pages = story.getPages();
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
        std::cout << e.what() << "\n";
        getline(std::cin, inputChoice);
        if (std::cin.eof()) {
          std::cerr << "The input cannot finish the story.\n";
          exit(EXIT_FAILURE);
        }
      }
      catch (EmptyInputException & e) {
        getline(std::cin, inputChoice);
        if (std::cin.eof()) {
          std::cerr << "The input cannot finish the story.\n";
          exit(EXIT_FAILURE);
        }
      }
      catch (InvalidChoiceException & e) {
        std::cout << e.what();
        // currentPage->printChoices();
        getline(std::cin, inputChoice);
        if (std::cin.eof()) {
          std::cerr << "The input cannot finish the story.\n";
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  currentPage->printPage();
  return EXIT_SUCCESS;
}
