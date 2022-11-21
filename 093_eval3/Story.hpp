#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//#include "util.hpp"
#include "Page.hpp"

class Story {
  std::vector<std::string> storyLines;
  int currentPageNum;
  std::vector<Page *> pageVec;

  std::string generatePath(const std::string path, const std::string file);
  int getLineType(std::string);

 public:
  Story() : currentPageNum(0){};
  Story(const std::string filePath);
  Story(const Story & rhs);
  Story & operator=(const Story & rhs);
  ~Story();
  //For Step 1
  void printStory();
};

std::string Story::generatePath(const std::string path, const std::string file) {
  std::ostringstream fileName;
  fileName << path << "/" << file;
  std::string filePath = fileName.str();
  return filePath;
}

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
      int pageNumber = std::strtoul(numOfPage.c_str(), NULL, 10);
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

void Story::printStory() {
  std::vector<Page *>::iterator it = pageVec.begin();
  while (it != pageVec.end()) {
    (*it)->printPage();
    it++;
  }
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
