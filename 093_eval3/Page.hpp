#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"
class Page {
  std::vector<std::pair<int, std::string> > choices;

  //which page is it?
  std::vector<std::string> pageInfo;
  size_t pageNum;
  //mode, 0 for normal, 1 for win, 2 for lose
  size_t goPageNum;
  int pageType;
  std::vector<std::string> pageText;

 public:
  Page() : pageNum(0), pageType(0){};
  Page(const std::string line, const std::string path);
  Page(const Page & rhs);
  Page & operator=(const Page & rhs);
  //  ~Page();
  //  std::string generatePath(const std::string path, const std::string file);
  int getPageNum() const { return pageNum; }
  int getPageType() const { return pageType; }
  size_t getDestination() const { return goPageNum; }
  void printPage();
  void addChoices(const std::string option);
  size_t getChoiceSize() { return choices.size(); };
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

Page::Page(std::string line, const std::string path) {
  size_t findAt = line.find("@");
  if (findAt != std::string::npos) {
    std::string numOfPage = line.substr(0, findAt);
    pageNum = std::strtoul(numOfPage.c_str(), NULL, 10);
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
      std::cerr << "Wrong input sstory!\n";
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

void Page::printPage() {
  std::cout << "Page " << pageNum << "\n";
  std::cout << "==========\n";
  std::vector<std::string>::iterator it = pageText.begin();
  while (it != pageText.end()) {
    std::cout << *it << "\n";
    it++;
  }
  std::cout << "\n";
  if (pageType == 0) {
    std::cout << "What would you like to do?\n";
    std::cout << "\n";
    std::vector<std::pair<int, std::string> >::iterator itC = choices.begin();
    int count = 1;
    while (itC != choices.end()) {
      std::cout << " " << count << ". " << (*itC).second << "\n";
      itC++;
      count++;
    }
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

void Page::addChoices(const std::string option) {
  size_t findCol = option.find(":");
  if (findCol != std::string::npos) {
    std::string choiceNum = option.substr(0, findCol);
    int page = std::atoi(choiceNum.c_str());
    std::string opContent = option.substr(findCol + 1);
    std::pair<int, std::string> newOption = std::make_pair(page, opContent);
    choices.push_back(newOption);
  }
  else {
    std::cerr << "Invalid Choice!\n";
    exit(EXIT_FAILURE);
  }
}
