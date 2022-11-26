#ifndef _PAGE_H__
#define _PAGE_H__
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Page.hpp"
#include "util.hpp"

class Story {
  std::vector<std::string> storyLines;
  int currentPageNum;
  std::vector<Page *> pageVec;

  int getLineType(std::string);

 public:
  Story() : currentPageNum(0){};
  Story(const std::string filePath);
  Story(const Story & rhs);
  Story & operator=(const Story & rhs);
  ~Story();
  //For Step 1
  size_t getStorySize() const { return pageVec.size(); }
  std::vector<Page *> & getPages() { return pageVec; }
  void printStory() const;
  void checkStory() const;
  void printStoryByInput() const;
  size_t getValidInput(std::string input, Page * curr) const;
};

int Story::getLineType(std::string line) {
  if (line.size() == 0) {
    return 0;
  }
  size_t findAt = line.find("@");
  if (findAt != std::string::npos) {
    size_t findCol = line.find(":");
    if (findCol != std::string::npos) {
      return 1;
    }
  }
  size_t findCol = line.find(":");
  if (findCol != std::string::npos) {
    size_t secondCol = line.substr(findCol + 1).find(":");
    if (secondCol != std::string::npos) {
      return 2;
    }
  }
  std::cerr << "Input StoryLine wrong.\n";
  exit(EXIT_FAILURE);
}

Story::Story(const std::string path) {
  std::string storyPath = generatePath(path, "story.txt");
  std::ifstream storyFile;
  storyFile.open(storyPath.c_str());
  if (!storyFile.is_open()) {
    std::cerr << "Cannot open the story.txt\n";
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (getline(storyFile, line)) {
    storyLines.push_back(line);
    if (getLineType(line) == 1) {
      Page * currentPage = new Page(line, path);
      pageVec.push_back(currentPage);
    }
    else if (getLineType(line) == 0) {
      continue;
    }
    else if (getLineType(line) == 2) {
      size_t findCol = line.find(":");
      std::string numOfPage = line.substr(0, findCol);
      size_t pageNumber = std::strtoul(numOfPage.c_str(), NULL, 10);
      Page * currentPage = pageVec[pageNumber];
      if (pageNumber != currentPage->getPageNum()) {
        std::cerr << "The choice cannot be matched with the current page.\n";
        exit(EXIT_FAILURE);
      }
      std::string option = line.substr(findCol + 1, line.size() - 1);
      currentPage->addChoices(option);
    }
    else {
      std::cerr << "Wrong storyLine type.\n";
      exit(EXIT_FAILURE);
    }
  }
  storyFile.close();
}

void Story::printStory() const {
  std::vector<Page *>::const_iterator it = pageVec.begin();
  while (it != pageVec.end()) {
    std::cout << "Page " << (*it)->getPageNum() << "\n";
    std::cout << "==========\n";
    (*it)->printPage();
    it++;
  }
}

void Story::checkStory() const {
  size_t prevPage = -1;
  bool hasWin = false;
  bool hasLose = false;
  for (size_t j = 0; j < getStorySize(); j++) {
    Page * current = pageVec[j];
    //check if the page is in order and consecutive
    if (current->getPageNum() != prevPage + 1) {
      std::cerr << "The pages are not consecutive.\n";
    }
    else {
      prevPage = current->getPageNum();
    }
    std::vector<std::pair<size_t, std::string> > choices = current->getChoices();
    for (size_t i = 0; i < choices.size(); i++) {
      std::pair<size_t, std::string> currentChoice = choices[i];
      if (currentChoice.first >= getStorySize()) {
        std::cerr << "The page number is not a match.\n";
      }
      Page * jumpTo = pageVec[currentChoice.first];
      if (jumpTo->getPageNum() != currentChoice.first) {
        std::cerr << "The page number is not a match.\n";
      }
      else {
        jumpTo->setVisited();
      }
    }
    if (current->getPageType() == 1) {
      hasWin = true;
    }
    else if (current->getPageType() == 2) {
      hasLose = true;
    }
  }
  if ((!hasWin) || (!hasLose)) {
    std::cerr << "No win or No lose page in this storty.\n";
  }
  for (size_t k = 1; k < getStorySize(); k++) {
    Page * currPage = pageVec[k];
    if (!currPage->checkVisited()) {
      std::cerr << "There are pages that are not referenced.\n";
    }
  }
}
size_t Story::getValidInput(std::string input, Page * currentPage) const {
  if (input.empty() || !checkValidNum(input)) {
    throw UserInputException();
  }
  size_t choice = std::strtoul(input.c_str(), NULL, 10);
  if (choice <= 0 || choice > currentPage->getChoiceSize()) {
    throw UserInputException();
  }
  return choice;
}

Story::Story(const Story & rhs) {
  currentPageNum = rhs.currentPageNum;
  storyLines = rhs.storyLines;
  for (size_t i = 0; i < rhs.pageVec.size(); i++) {
    Page copyPage(*rhs.pageVec[i]);
    pageVec.push_back(&copyPage);
  }
}

Story & Story::operator=(const Story & rhs) {
  if (this != &rhs) {
    Story temp(rhs);
    std::swap(storyLines, temp.storyLines);
    std::swap(currentPageNum, temp.currentPageNum);
    std::swap(pageVec, temp.pageVec);
  }
  return *this;
}

Story::~Story() {
  size_t size = pageVec.size();
  for (size_t i = 0; i < size; i++) {
    delete pageVec[i];
  }
}

#endif
