#ifndef _Story_H__
#define _Story_H__
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Page.hpp"
#include "util.hpp"

class Story {
  std::vector<std::string> storyLines;
  std::vector<Page *> pageVec;
  std::vector<std::vector<std::pair<int, int> > > successPath;
  std::map<std::string, long> storyVar;
  int getLineType(std::string);
  void dfs(Page *, std::vector<std::pair<int, int> > path);
  //return the index of var, if not exist, return -1
  bool isNewVariable(std::string variable);

 public:
  Story(){};
  Story(const std::string filePath);
  Story(const Story & rhs);
  Story & operator=(const Story & rhs);
  ~Story();
  size_t getStorySize() const { return pageVec.size(); }
  std::vector<Page *> & getPages() { return pageVec; }
  void printStory() const;
  void checkStory() const;
  void printStoryByInput() const;
  size_t getValidInput(std::string input, Page * curr) const;
  void printSuccessPath() const;
  void searchSuccessPath();
  void setStoryVar(std::string, long value);
  void updateStoryVar(Page * currentPage);
  void updatePageValidChoice(Page * currentPage);
};

//Check the type of the line
//0. empty line, not an error
//1:Normal page declaration
//2. Add choice without condition
//3. Save story variable to the page
//4. Add choice with condition
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
      size_t findLeftBracket = line.substr(0, findCol).find("[");
      size_t findRightBracket = line.substr(0, findCol).find("[");
      size_t findEq = line.substr(0, findCol).find("=");
      if (findLeftBracket != std::string::npos && findRightBracket != std::string::npos &&
          findEq != std::string::npos) {
        return 4;
      }
      else {
        return 2;
      }
    }
  }
  if ((line.find("=") != std::string::npos) && (line.find("$") != std::string::npos)) {
    return 3;
  }
  std::cerr << "The story contains invalid input line.\n";
  exit(EXIT_FAILURE);
}

//Input: the path of the story directory
Story::Story(const std::string path) {
  //Merge the directory with the story.txt
  std::string storyPath = generatePath(path, "story.txt");
  std::ifstream storyFile;
  storyFile.open(storyPath.c_str());
  if (!storyFile.is_open()) {
    std::cerr << "Cannot open the story.txt in the story directory\n";
    exit(EXIT_FAILURE);
  }
  //Read the story line by line
  std::string line;
  while (getline(storyFile, line)) {
    storyLines.push_back(line);
    //If it is the  page declaration line
    if (getLineType(line) == 1) {
      Page * currentPage = new Page(line, path);
      pageVec.push_back(currentPage);
    }
    //If the line is empty
    else if (getLineType(line) == 0) {
      continue;
    }

    //If it is a choice line (With or without condition)
    else if (getLineType(line) == 2 || getLineType(line) == 4) {
      size_t findCol = line.find(":");
      size_t findBr = line.find("[");
      std::string numOfPage;
      //If the line contains "[", it is of type 4
      if (findBr != std::string::npos) {
        numOfPage = line.substr(0, findBr);
      }
      else {
        numOfPage = line.substr(0, findCol);
      }
      size_t pageNumber = std::strtoul(numOfPage.c_str(), NULL, 10);
      if (pageNumber >= pageVec.size()) {
        std::cerr
            << "The current page of the choice shows up before the page declaration.\n";
        exit(EXIT_FAILURE);
      }
      Page * currentPage = pageVec[pageNumber];
      if (pageNumber != currentPage->getPageNum()) {
        std::cerr << "The choice cannot be matched with the current page.\n";
        exit(EXIT_FAILURE);
      }
      // std::string option = line.substr(0, line.size() - 1);
      //add the choice into the current page
      int type = getLineType(line);
      currentPage->addChoices(line, type);
    }

    //If it is the line that change the story variable
    else if (getLineType(line) == 3) {
      size_t findTerm = line.find("$");
      std::string pageNum = line.substr(0, findTerm);
      size_t pageNumber = std::strtoul(pageNum.c_str(), NULL, 10);
      Page * currentPage = pageVec[pageNumber];
      std::string variable = line.substr(findTerm + 1);
      //If it is a new variable, add it into the story variable aray
      if (isNewVariable(variable)) {
        storyVar[variable] = 0;
      }
      currentPage->addUpdateVarable(variable);
    }
    else {
      std::cerr << "Wrong storyLine type.\n";
      exit(EXIT_FAILURE);
    }
  }
  storyFile.close();
}

//When the page that changes the story variable is called, update the variable status in the variable array
void Story::updateStoryVar(Page * currentPage) {
  Page::Variables * pageVar = currentPage->getPageVar();
  std::vector<std::pair<std::string, long> >::iterator it = pageVar->variables.begin();
  while (it != pageVar->variables.end()) {
    storyVar[(*it).first] = (*it).second;
    it++;
  }
}

//Everytime the story variable changes, update the choice status of the current page
void Story::updatePageValidChoice(Page * currentPage) {
  std::vector<Page::Choice *> pageChoice = currentPage->getChoices();
  for (size_t i = 0; i < pageChoice.size(); i++) {
    std::pair<std::string, long> choiceCondition = pageChoice[i]->choiceCondition;
    if (storyVar.find(choiceCondition.first) == storyVar.end()) {
      std::cerr << "The story contians page in which the variable of the choices does "
                   "not exist.";
      exit(EXIT_FAILURE);
    }
    if (storyVar[choiceCondition.first] != choiceCondition.second) {
      pageChoice[i]->isAvailable = false;
    }
    else {
      pageChoice[i]->isAvailable = true;
    }
  }
}

//When read the line of story variable, check if it is new variable
bool Story::isNewVariable(std::string variable) {
  std::map<std::string, long>::iterator it = storyVar.begin();
  while (it != storyVar.end()) {
    if ((*it).first.compare(variable) == 0) {
      return false;
    }
    it++;
  }
  return true;
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

//Check if this story has valid format
void Story::checkStory() const {
  size_t prevPage = -1;
  bool hasWin = false;
  bool hasLose = false;
  for (size_t j = 0; j < getStorySize(); j++) {
    Page * current = pageVec[j];
    //check if the page is in order and consecutive
    if (current->getPageNum() != prevPage + 1) {
      std::cerr << "The pages in this story are not consecutive.\n";
      exit(EXIT_FAILURE);
    }
    else {
      prevPage = current->getPageNum();
    }

    //If this is a win or lose page, update the hasWin/Lose flag and assert they have no choice
    if (current->getPageType() == 1) {
      hasWin = true;
      if (current->getChoiceSize() != 0) {
        std::cerr << "The win page of the story has choices, but it shouldn't.\n";
      }
    }
    else if (current->getPageType() == 2) {
      hasLose = true;
      if (current->getChoiceSize() != 0) {
        std::cerr << "The lose page of the story has choices, but it shouldn't.\n";
      }
    }

    //If the page is neither win or lose, check the choices
    else {
      std::vector<Page::Choice *> choices = current->getChoices();
      for (size_t i = 0; i < choices.size(); i++) {
        Page::Choice * currentChoice = choices[i];
        //If the destination page does not exist
        if (currentChoice->choiceContent.first < 0 ||
            currentChoice->choiceContent.first >= getStorySize()) {
          std::cerr << "The story contains page that the destination page of its choice "
                       "does not exist.\n";
          exit(EXIT_FAILURE);
        }
        Page * jumpToPage = pageVec[currentChoice->choiceContent.first];
        //The actual destination page is different from what we want
        //This situation should never happen, just in case
        if (jumpToPage->getPageNum() != currentChoice->choiceContent.first) {
          std::cerr << "The page number is not a match.\n";
          exit(EXIT_FAILURE);
        }
        if (jumpToPage->getPageNum() == current->getPageNum()) {
          //This dest page of current choice is the same of its current page, we should not set this page as referenced
          continue;  //should it be an error? Check later
        }
        else {
          jumpToPage->setReferenced();
        }
      }
    }
  }

  //After looping, check if there are win and lose page, and every page is referenced at least once by others
  if ((!hasWin) || (!hasLose)) {
    std::cerr << "No win or No lose page in this storty.\n";
    exit(EXIT_FAILURE);
  }
  //Start from 1, we don't need to check if page 0 is referenced by others
  for (size_t k = 1; k < getStorySize(); k++) {
    Page * currPage = pageVec[k];
    if (!currPage->checkReferenced()) {
      std::cerr << "There are pages that are not referenced in this story.\n";
      exit(EXIT_FAILURE);
    }
  }
}

//Check if the user input is a valid one
size_t Story::getValidInput(std::string input, Page * currentPage) const {
  //invalid case:No input/input is not a number
  //The input is not a valid choice for current page
  //The input choice is unavailable under the story variables
  if (input.empty() || !checkValidNum(input)) {
    throw UserInputException();
  }
  size_t choice = std::strtoul(input.c_str(), NULL, 10);
  if (choice <= 0 || choice > currentPage->getChoiceSize()) {
    throw UserInputException();
  }
  std::vector<Page::Choice *> currentChoices = currentPage->getChoices();
  if (!currentChoices[choice - 1]->isAvailable) {
    throw InvalidChoiceException();
  }
  return choice;
}

//dfs algorithm
void Story::dfs(Page * current, std::vector<std::pair<int, int> > path) {
  //Base Case: We found a win/lose page,
  //or the page has already been visited, which means this path is a loop, go back
  if (current->isWinPage()) {
    path.push_back(std::make_pair(current->getPageNum(), -1));
    std::vector<std::pair<int, int> > pathCopy(path);
    successPath.push_back(pathCopy);
    return;
  }
  else if (current->isLostPage()) {
    return;
  }
  else if (current->checkVisited() == true) {
    return;
  }
  else {
    //Set the current page as visited
    current->setVisited();
    std::vector<Page::Choice *> currentChoice = current->getChoices();
    std::vector<Page::Choice *>::iterator it = currentChoice.begin();
    int choiceNum = 1;
    //Loop all the possible direct destination from the current page
    while (it != currentChoice.end()) {
      path.push_back(std::make_pair(current->getPageNum(), choiceNum));
      //Check the destination page for this chice
      Page * dest = pageVec[(*it)->choiceContent.first];
      dfs(dest, path);
      //this dest is either a wil page (stored the path, clean the visited record and start a new one)
      //or not eligible (wipe the visited record and start a new path)
      dest->eraseVisited();
      path.pop_back();
      choiceNum++;
      it++;
    }
  }
}

//Invoke dfs to search for success path
void Story::searchSuccessPath() {
  Page * current = pageVec[0];
  std::vector<std::pair<int, int> > path(0);
  dfs(current, path);
}

void Story::printSuccessPath() const {
  if (successPath.size() == 0) {
    std::cout << "This story is unwinnable!\n";
  }
  for (size_t i = 0; i < successPath.size(); i++) {
    std::vector<std::pair<int, int> > currentPath = successPath[i];
    for (size_t j = 0; j < currentPath.size(); j++) {
      std::pair<int, int> currentPage = currentPath[j];
      if (currentPage.second == -1) {
        std::cout << currentPage.first << "(win)\n";
      }
      else {
        std::cout << currentPage.first << "(" << currentPage.second << "),";
      }
    }
  }
}

//Rule of Three
Story::Story(const Story & rhs) {
  storyLines = rhs.storyLines;
  successPath = rhs.successPath;
  storyVar = rhs.storyVar;
  for (size_t i = 0; i < rhs.pageVec.size(); i++) {
    Page * copyPage = new Page(*(rhs.pageVec[i]));
    pageVec.push_back(copyPage);
  }
}

Story & Story::operator=(const Story & rhs) {
  if (this != &rhs) {
    Story temp(rhs);
    std::swap(storyLines, temp.storyLines);
    std::swap(pageVec, temp.pageVec);
    std::swap(successPath, temp.successPath);
    std::swap(storyVar, temp.storyVar);
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
