#ifndef _Page_H__
#define _Page_H__
#include <cassert>
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
    bool hasCon;
    bool isAvailable;
    Choice(){};
    Choice(std::pair<size_t, std::string> content, bool hasCon, bool avail) :
        choiceContent(content), hasCon(hasCon), isAvailable(avail){};
    Choice(std::pair<size_t, std::string> content,
           std::pair<std::string, long> choiceCond,
           bool hasCon,
           bool avail) :
        choiceContent(content),
        choiceCondition(choiceCond),
        hasCon(hasCon),
        isAvailable(avail){};
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
  int pageType;
  bool referenced;
  bool visited;
  std::vector<std::string> pageText;
  std::vector<Choice *> choices;
  Variables * pageVariables;
  int extractPageType(std::string typeOfPage);
  std::pair<std::string, size_t> setChoiceCondition(const std::string option);

 public:
  Page() : pageNum(0), pageType(0){};
  Page(const std::string line, const std::string path);
  Page(const Page & rhs);
  Page & operator=(const Page & rhs);
  ~Page();
  size_t getPageNum() const { return pageNum; }
  int getPageType() const { return pageType; }
  void addChoices(const std::string option, int lineType);
  size_t getChoiceSize() const { return choices.size(); }
  std::vector<Choice *> getChoices() const { return choices; }
  Variables * getPageVar() const { return pageVariables; }
  void setVisited() { visited = true; }
  void setReferenced() { referenced = true; }
  void eraseVisited() { visited = false; }
  bool checkVisited() const { return visited; }
  bool checkReferenced() const { return referenced; }
  bool isWinPage() const { return pageType == 1; }
  bool isLostPage() const { return pageType == 2; }
  void addUpdateVarable(const std::string line);
  void printPage() const;
  void printChoices() const;
};

//Get the type of current page. N = 0, W = 1, L = 2
int Page::extractPageType(std::string typeOfPage) {
  int type = -1;
  if (typeOfPage == "N") {
    type = 0;
  }
  else if (typeOfPage == "W") {
    type = 1;
  }
  else if (typeOfPage == "L") {
    type = 2;
  }
  else {
    std::cerr << "This story contains undefined page (not N, W nor L).\n";
    exit(EXIT_FAILURE);
  }
  return type;
}

//Note: This page constructor will only be called if the story input line is to declare a page(contains @)
//If the line is of other three types, we should not call the constructor
Page::Page(std::string line, const std::string path) {
  //initialize variables of a new page
  visited = false;
  referenced = false;
  pageVariables = new Variables();

  size_t findAt = line.find("@");
  //The first type of input lines (The one contains @)
  if (findAt != std::string::npos) {
    std::string numOfPage = line.substr(0, findAt);
    //Check if the number of this page is valid
    if (checkValidNum(numOfPage)) {
      pageNum = std::strtoul(numOfPage.c_str(), NULL, 10);
    }
    else {
      //page number os not a valid number
      std::cerr << "This story contains invalid Page number.\n";
    }
  }
  else {
    std::cerr << "This line should not be used to construct a new page.\n";
    exit(EXIT_FAILURE);
  }
  //Extract the type of this page
  size_t findCol = line.find(":");
  if (findCol != std::string::npos) {
    std::string typeOfPage = line.substr(findAt + 1, 1);
    pageType = extractPageType(typeOfPage);
    assert(pageType >= 0);
  }
  else {
    std::cerr << "This story contains page declaration line has not declare a correct "
                 "page type.\n";
    exit(EXIT_FAILURE);
  }
  //Extract the content from the file of this page
  const std::string fileName = line.substr(findCol + 1);
  //merge the file name and the directory
  std::string filePath = generatePath(path, fileName);
  std::ifstream pageFile;
  std::string pageLine;
  pageFile.open(filePath.c_str(), std::ios_base::in);
  if (!pageFile.is_open()) {
    std::cerr << "The story contains page declaration line that its page file cannot be "
                 "opened.\n";
    exit(EXIT_FAILURE);
  }
  //Write the content of the page into the pageText for further display
  while (getline(pageFile, pageLine)) {
    pageText.push_back(pageLine);
  }
  pageFile.close();
}

//Display all the choices of current page
void Page::printChoices() const {
  std::vector<Choice *>::const_iterator itC = choices.begin();
  int count = 1;
  while (itC != choices.end()) {
    //If the choice is available under current story variables
    if (!(*itC)->hasCon) {
      std::cout << " " << count << ". " << (*itC)->choiceContent.second << "\n";
    }
    else {
      if ((*itC)->isAvailable) {
        std::cout << " " << count << ". " << (*itC)->choiceContent.second << "\n";
      }
      //If the choice is not available
      else {
        std::cout << " " << count << ". <UNAVAILABLE>\n";
      }
    }
    itC++;
    count++;
  }
}

void Page::printPage() const {
  std::vector<std::string>::const_iterator it = pageText.begin();
  //First print out the content of the page
  while (it != pageText.end()) {
    std::cout << *it << "\n";
    it++;
  }
  std::cout << "\n";
  //Second, if it is a normal page, print out all the possible choices
  if (pageType == 0) {
    std::cout << "What would you like to do?\n";
    std::cout << "\n";
    printChoices();
  }
  //if it is a win page, congratulate the player!
  else if (pageType == 1) {
    std::cout << "Congratulations! You have won. Hooray!\n";
  }
  //if it is a lose page, print lose
  else if (pageType == 2) {
    std::cout << "Sorry, you have lost. Better luck next time!\n";
  }
  //The pagetype is not a valid type. This situation should never exist
  else {
    std::cerr << "Wrong pageType\n";
  }
}

//When read the story.txt, if this page changes the story variable, add it into the variables object
//If the page is visited when playing, we weill change the story variable according to this object
void Page ::addUpdateVarable(const std::string line) {
  size_t findEq = line.find("=");
  std::string var = line.substr(0, findEq);
  std::string val = line.substr(findEq + 1);
  if (checkValidLong(val) == false) {
    std::cerr << "The story has condition value that is not a long.\n";
    exit(EXIT_FAILURE);
  }
  long value = std::strtol(val.c_str(), NULL, 10);
  std::pair<std::string, long> variable = std::make_pair(var, value);
  pageVariables->variables.push_back(variable);
}

//Extract the choice condition from the input line
std::pair<std::string, size_t> Page::setChoiceCondition(const std::string option) {
  std::string condition =
      option.substr((option.find("[") + 1), option.find("]") - option.find("["));
  size_t findEq = condition.find("=");
  std::string var = condition.substr(0, findEq);
  std::string val = condition.substr(findEq + 1);
  long value = std::strtol(val.c_str(), NULL, 10);
  std::pair<std::string, long> choiceCond = std::make_pair(var, value);
  return choiceCond;
}

//Note: This method should only be invoked if the input story line is of type two or type four
//and the currentPage of the choice should match "this" page, this should be checked when invoked the function in story.hpp
void Page::addChoices(const std::string option, int lineType) {
  if (lineType != 2 && lineType != 4) {
    std::cerr << "The story line contains choice line that is not in correct format.\n";
    exit(EXIT_FAILURE);
  }
  size_t firstCol = option.find(":");
  if (firstCol != std::string::npos) {
    size_t findCol = (option.substr(firstCol + 1)).find(":");
    if (findCol != std::string::npos) {
      //get the destination page between the two ":"
      std::string destNum = option.substr(firstCol + 1, findCol);
      size_t destPage;
      if (checkValidNum(destNum)) {
        destPage = std::atoi(destNum.c_str());
      }
      else {
        std::cerr << "The story contains line that the destination of the choice is a "
                     "invalid Page number.\n";
      }
      //Initialize a new choice object and write the info of this choice into it
      std::string opContent = option.substr(findCol + firstCol + 2);
      std::pair<int, std::string> newOption = std::make_pair(destPage, opContent);
      //If this choice requires condition, write the condition into the object
      //If the choice has no conditon, do not write the condition
      if (lineType == 4) {
        std::pair<std::string, long> choiceCondition = setChoiceCondition(option);
        Choice * newChoice = new Choice(newOption, choiceCondition, true, true);
        choices.push_back(newChoice);
      }
      else {
        Choice * newChoice = new Choice(newOption, false, true);
        choices.push_back(newChoice);
      }
    }
    else {
      std::cerr << "Invalid Choice!\n";
      exit(EXIT_FAILURE);
    }
  }
}

//Rule of three
Page::Page(const Page & rhs) {
  pageType = rhs.pageType;
  pageNum = rhs.pageNum;
  pageText.clear();
  pageInfo.clear();
  for (size_t i = 0; i < rhs.pageInfo.size(); i++) {
    pageInfo.push_back(rhs.pageInfo[i]);
  }
  for (size_t i = 0; i < rhs.pageText.size(); i++) {
    pageText.push_back(rhs.pageText[i]);
  }
  for (size_t i = 0; i < rhs.choices.size(); i++) {
    Choice * current = new Choice();
    *current = (*(rhs.choices[i]));
    choices.push_back(current);
  }
  pageVariables = new Variables();
  *pageVariables = *(rhs.pageVariables);
}

Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    Page temp(rhs);
    std::swap(pageType, temp.pageType);
    std::swap(pageNum, temp.pageNum);
    std::swap(pageInfo, temp.pageInfo);
    std::swap(pageText, temp.pageText);
    std::swap(choices, temp.choices);
    std::swap(*pageVariables, *rhs.pageVariables);
  }
  return *this;
}

Page::~Page() {
  delete pageVariables;
  for (size_t i = 0; i < choices.size(); i++) {
    delete choices[i];
  }
  choices.clear();
}
#endif
