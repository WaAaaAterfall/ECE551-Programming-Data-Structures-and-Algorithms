#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"
class Page {
 public:
  class Choice {
   public:
    std::pair<size_t, std::string> choiceContent;
    std::pair<std::string, long> choiceCondition;
    bool isAvailable;
  };

  class Variables {
   public:
    std::vector<std::pair<std::string, long> > variables;
  };

 private:
  //which page is it?
  std::vector<std::string> pageInfo;
  size_t pageNum;
  //mode, 0 for normal, 1 for win, 2 for lose
  size_t goPageNum;
  int pageType;
  std::vector<std::string> pageText;
  bool referenced;
  bool visited;
  std::vector<Choice *> choices;
  Variables * pageVariables;

 public:
  Page() : pageNum(0), pageType(0){};
  Page(const std::string line, const std::string path);
  Page(const Page & rhs);
  Page & operator=(const Page & rhs);
  ~Page();
  size_t getPageNum() const { return pageNum; }
  int getPageType() const { return pageType; }
  size_t getDestination() const { return goPageNum; }
  void printPage() const;
  void printChoices() const;
  void addChoices(const std::string option, int lineType);
  size_t getChoiceSize() const { return choices.size(); }
  std::vector<Choice *> getChoices() const { return choices; }
  Variables * getPageVar() const { return pageVariables; }
  void addUpdateVarable(const std::string line);
  void setVisited() { visited = true; }
  void setReferenced() { referenced = true; }
  void eraseVisited() { visited = false; }
  bool checkVisited() const { return visited; }
  bool checkReferenced() const { return referenced; }
  bool isWinPage() const { return pageType == 1; }
  bool isLostPage() const { return pageType == 2; }
};

//Rule of three
Page::Page(const Page & rhs) {
  pageType = rhs.pageType;
  goPageNum = rhs.goPageNum;
  pageNum = rhs.pageNum;
  pageText.clear();
  pageInfo.clear();
  for (size_t i = 0; i < rhs.pageInfo.size(); i++) {
    pageInfo.push_back(rhs.pageInfo[i]);
  }
  for (size_t i = 0; i < rhs.pageText.size(); i++) {
    pageText.push_back(rhs.pageText[i]);
  }
  for (size_t i = 0; i < choices.size(); i++) {
    choices.push_back(rhs.choices[i]);
  }
}

Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    Page temp(rhs);
    std::swap(pageType, temp.pageType);
    std::swap(goPageNum, temp.goPageNum);
    std::swap(pageNum, temp.pageNum);
    std::swap(pageInfo, temp.pageInfo);
    std::swap(pageText, temp.pageText);
    std::swap(choices, temp.choices);
  }
  return *this;
}
Page::~Page() {
  delete pageVariables;
  for (size_t i = 0; i < choices.size(); i++) {
    delete choices[i];
  }
}

Page::Page(std::string line, const std::string path) {
  visited = false;
  referenced = false;
  pageVariables = new Variables();
  size_t findAt = line.find("@");
  if (findAt != std::string::npos) {
    std::string numOfPage = line.substr(0, findAt);
    if (checkValidNum(numOfPage)) {
      pageNum = std::strtoul(numOfPage.c_str(), NULL, 10);
    }
    else {
      std::cerr << "Invalid Page number.\n";
    }
  }
  else {
    std::cerr << "Wrong input story!\n";
    exit(EXIT_FAILURE);
  }
  size_t findCol = line.find(":");
  if (findCol != std::string::npos) {
    std::string typeOfPage = line.substr(findAt + 1, 1);
    if (typeOfPage == "N") {
      pageType = 0;
    }
    else if (typeOfPage == "W") {
      pageType = 1;
    }
    else if (typeOfPage == "L") {
      pageType = 2;
    }
    else {
      std::cerr << "Invalid page type!\n";
      exit(EXIT_FAILURE);
    }
  }
  else {
    std::cerr << "Wrong input sstory!\n";
    exit(EXIT_FAILURE);
  }
  const std::string fileName = line.substr(findCol + 1);
  std::string filePath = generatePath(path, fileName);
  std::ifstream pageFile;
  std::string pageLine;
  pageFile.open(filePath.c_str(), std::ios_base::in);
  if (!pageFile.is_open()) {
    std::cerr << "Cannot open the file\n";
    exit(EXIT_FAILURE);
  }
  while (getline(pageFile, pageLine)) {
    pageText.push_back(pageLine);
  }
  pageFile.close();
}

void Page::printChoices() const {
  std::vector<Choice *>::const_iterator itC = choices.begin();
  int count = 1;
  while (itC != choices.end()) {
    if ((*itC)->isAvailable) {
      std::cout << " " << count << ". " << (*itC)->choiceContent.second << "\n";
    }
    else {
      std::cout << " " << count << ". <UNAVAILABLE>\n";
    }
    itC++;
    count++;
  }
}

void Page::printPage() const {
  std::vector<std::string>::const_iterator it = pageText.begin();
  while (it != pageText.end()) {
    std::cout << *it << "\n";
    it++;
  }
  std::cout << "\n";
  if (pageType == 0) {
    std::cout << "What would you like to do?\n";
    std::cout << "\n";
    printChoices();
  }
  else if (pageType == 1) {
    std::cout << "Congratulations! You have won. Hooray!\n";
  }
  else if (pageType == 2) {
    std::cout << "Sorry, you have lost. Better luck next time!\n";
  }
  else {
    std::cerr << "Wrong pageType\n";
  }
}

void Page ::addUpdateVarable(const std::string line) {
  size_t findEq = line.find("=");
  std::string var = line.substr(0, findEq);
  std::string val = line.substr(findEq + 1);
  size_t value = std::strtoul(val.c_str(), NULL, 10);
  std::pair<std::string, size_t> variable = std::make_pair(var, value);
  pageVariables->variables.push_back(variable);
}

void Page::addChoices(const std::string option, int lineType) {
  size_t firstCol = option.find(":");
  size_t findCol = (option.substr(firstCol + 1)).find(":");
  if (findCol != std::string::npos) {
    std::string destNum = option.substr(firstCol + 1, findCol);
    size_t destPage;
    if (checkValidNum(destNum)) {
      destPage = std::atoi(destNum.c_str());
    }
    else {
      std::cerr << "Invalid Page number.\n";
    }
    std::string opContent = option.substr(findCol + firstCol + 2);
    Choice * newOp = new Choice();
    std::pair<int, std::string> newOption = std::make_pair(destPage, opContent);
    newOp->choiceContent = newOption;
    newOp->isAvailable = true;
    if (lineType == 4) {
      std::string condition =
          option.substr((option.find("[") + 1), option.find("]") - option.find("["));
      size_t findEq = condition.find("=");
      std::string var = condition.substr(0, findEq);
      std::string val = condition.substr(findEq + 1);
      size_t value = std::strtoul(val.c_str(), NULL, 10);
      newOp->choiceCondition = std::make_pair(var, value);
    }
    choices.push_back(newOp);
  }
  else {
    std::cerr << "Invalid Choice!\n";
    exit(EXIT_FAILURE);
  }
}
