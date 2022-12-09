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
  //A vector to store all the pages in the story
  std::vector<Page *> pageVec;
  //A vector ro store all the possible success path (step 3)
  std::vector<std::vector<std::pair<int, int> > > successPath;
  //A map to store all the variables for this story(step4)
  std::map<std::string, long> storyVar;

  //private functions
  //get the type of the line
  //1: page declaration
  //2:choice without condition
  //3: page update variable
  //4: choice with condition
  int getLineType(std::string & line);
  //dfs algirirhm for step3
  void dfs(Page *, std::vector<std::pair<int, int> > path);
  //check if the variable is new to the story when read type 3 input line
  //return the index of var, if not exist, return -1
  bool isNewVariable(std::string & variable);

 public:
  Story(){};
  //A constructor with story path
  Story(const std::string & filePath);
  //rule of three
  Story(const Story & rhs);
  Story & operator=(const Story & rhs);
  ~Story();
  //return the page number of the story
  size_t getStorySize() const { return pageVec.size(); }
  //get the array of all the page
  std::vector<Page *> & getPages() { return pageVec; }
  //print the whole story(step1)
  void printStory() const;
  //Check if the story have the correct format (step1)
  void checkStoryFormat() const;
  //check if it is a valid story (step 2)
  void checkStory() const;
  //check if the user input is valid and return the valid number of choice
  size_t getValidInput(std::string & input, Page * curr) const;
  //print the successful path in right format
  void printSuccessPath() const;
  //search all the successful path in the story using dfs
  void searchSuccessPath();
  //update the story variable when visiting a new page
  void updateStoryVar(Page * currentPage);
  //Every time visit a new page, update the variables it needs for choices
  //according to the current story variable
  void updatePageValidChoice(Page * currentPage);
};

//Check the type of the line
//0. empty line, not an error
//1:Normal page declaration
//2. Add choice without condition
//3. Save story variable to the page
//4. Add choice with condition
int Story::getLineType(std::string & line) {
  if (line.size() == 0) {
    return 0;
  }
  //Case one sign: contains @ and :
  size_t findAt = line.find("@");
  if (findAt != std::string::npos) {
    size_t findCol = line.find(":");
    if (findCol != std::string::npos) {
      return 1;
    }
  }
  //Case 2 sign: two different :
  size_t findCol = line.find(":");
  if (findCol != std::string::npos) {
    size_t secondCol = line.substr(findCol + 1).find(":");
    if (secondCol != std::string::npos) {
      std::string pageAndCond = line.substr(0, findCol);
      size_t findLeftBracket = pageAndCond.find("[");
      if (findLeftBracket != std::string::npos) {
        size_t findRightBracket = pageAndCond.substr(findLeftBracket).find("]");
        if (findRightBracket != std::string::npos) {
          return 4;
        }
      }
      //If there is no [ and ], take it as case 2
      return 2;
    }
  }
  if ((line.find("=") != std::string::npos) && (line.find("$") != std::string::npos)) {
    return 3;
  }
  std::cerr << "The story contains invalid input line.\n";
  exit(EXIT_FAILURE);
}

//Input: the path of the story directory
Story::Story(const std::string & path) {
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
    //Case 1, If it is the  page declaration line
    if (getLineType(line) == 1) {
      //Page * currentPage = new Page(line, path);
      pageVec.push_back(new Page(line, path));
    }
    //Case 0: If the line is empty
    else if (getLineType(line) == 0) {
      continue;
    }

    //Case2 & 4: If it is a choice line (With or without condition)
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
      //check if it is a valid page number
      if (!checkValidNum(numOfPage)) {
        std::cerr << "The pagenumber is not valid in the story.\n";
        exit(EXIT_FAILURE);
      }
      size_t pageNumber = std::strtoul(numOfPage.c_str(), NULL, 10);
      if (pageNumber >= pageVec.size()) {
        std::cerr
            << "The current page of the choice shows up before the page declaration.\n";
        exit(EXIT_FAILURE);
      }
      //It is valid a valid page, so find the page
      Page * currentPage = pageVec[pageNumber];
      if (pageNumber != currentPage->getPageNum()) {
        std::cerr << "The choice cannot be matched with the current page.\n";
        exit(EXIT_FAILURE);
      }
      //add the choice into the current page
      int type = getLineType(line);
      currentPage->addChoices(line, type);
    }

    //Case3: If it is the line that change the story variable
    else if (getLineType(line) == 3) {
      size_t findTerm = line.find("$");
      std::string pageNum = line.substr(0, findTerm);
      if (checkValidNum(pageNum)) {
        size_t pageNumber = std::strtoul(pageNum.c_str(), NULL, 10);
        if (pageNumber >= pageVec.size()) {
          std::cerr << "The page does not exist for its variable.\n";
          exit(EXIT_FAILURE);
        }
        Page * currentPage = pageVec[pageNumber];
        std::string varAndVal = line.substr(findTerm + 1);
        size_t findEq = varAndVal.find("=");
        //If it is a new variable, add it into the story variable array
        std::string variable = varAndVal.substr(0, findEq);
        if (isNewVariable(variable)) {
          storyVar[variable] = 0;
        }
        currentPage->addUpdateVarable(varAndVal);
      }
    }

    //If the line is not the above five cases, it should be an error
    else {
      std::cerr << "Wrong storyLine type.\n";
      exit(EXIT_FAILURE);
    }
  }
  storyFile.close();
}

//When the page that changes the story variable is called, update the variable status in the variable array(Step4)
void Story::updateStoryVar(Page * currentPage) {
  std::vector<std::pair<std::string, long> > pageVar = currentPage->getPageVar();
  std::vector<std::pair<std::string, long> >::iterator it = pageVar.begin();
  while (it != pageVar.end()) {
    if (storyVar.find((*it).first) == storyVar.end()) {
      std::cerr << "The story contians page in which the variable of the choices does "
                   "not exist.";
      exit(EXIT_FAILURE);
    }
    storyVar[(*it).first] = (*it).second;
    it++;
  }
}

//Everytime the story variable changes, update the choice status of the current page(Step4)
void Story::updatePageValidChoice(Page * currentPage) {
  std::vector<Page::Choice *> pageChoice = currentPage->getChoices();
  for (size_t i = 0; i < pageChoice.size(); i++) {
    if (pageChoice[i]->hasCon) {
      std::pair<std::string, long> choiceCondition = pageChoice[i]->choiceCondition;
      if (storyVar[choiceCondition.first] != choiceCondition.second) {
        pageChoice[i]->isAvailable = false;
      }
      else {
        pageChoice[i]->isAvailable = true;
      }
    }
  }
}

//When read the line of story variable, check if it is new variable
bool Story::isNewVariable(std::string & variable) {
  std::map<std::string, long>::iterator it = storyVar.begin();
  while (it != storyVar.end()) {
    if ((*it).first.compare(variable) == 0) {
      return false;
    }
    it++;
  }
  return true;
}

//Directly print the whole story (step1)
void Story::printStory() const {
  std::vector<Page *>::const_iterator it = pageVec.begin();
  while (it != pageVec.end()) {
    std::cout << "Page " << (*it)->getPageNum() << "\n";
    std::cout << "==========\n";
    (*it)->printPage();
    it++;
  }
}

//Check if the story has the correct format(Step1)
void Story::checkStoryFormat() const {
  size_t nextPage = 1;
  for (size_t j = 0; j < getStorySize(); j++) {
    Page * current = pageVec[j];
    //check if the page is in order and consecutive
    if ((current->getPageNum() + 1) != nextPage) {
      std::cerr << "The pages in this story are not consecutive.\n";
      exit(EXIT_FAILURE);
    }
    else {
      nextPage++;
    }
    //If this is a win or lose page, assert they have no choice
    if (current->getPageType() == 1) {
      if (current->getChoiceSize() != 0) {
        std::cerr << "The win page of the story has choices, but it shouldn't.\n";
        exit(EXIT_FAILURE);
      }
    }
    else if (current->getPageType() == 2) {
      if (current->getChoiceSize() != 0) {
        std::cerr << "The lose page of the story has choices, but it shouldn't.\n";
        exit(EXIT_FAILURE);
      }
    }
  }
}

//Check if this story is valid (Step 2)
void Story::checkStory() const {
  checkStoryFormat();
  bool hasWin = false;
  bool hasLose = false;
  for (size_t j = 0; j < getStorySize(); j++) {
    Page * current = pageVec[j];
    //If the page is win or lose, update the flags
    if (current->getPageType() == 1) {
      hasWin = true;
    }
    else if (current->getPageType() == 2) {
      hasLose = true;
    }
    //If the page is neither win or lose, check the choices
    else {
      std::vector<Page::Choice *> choices = current->getChoices();
      for (size_t i = 0; i < choices.size(); i++) {
        Page::Choice * currentChoice = choices[i];
        //If the destination page does not exist, not page to reference
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
size_t Story::getValidInput(std::string & input, Page * currentPage) const {
  //invalid case:No input/input is not a number
  //The input is not a valid choice for current page
  //The input choice is unavailable under the story variables
  if (input.empty()) {
    throw EmptyInputException();
  }
  if (!checkValidInputNum(input)) {
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
    size_t choiceNum = 1;
    //Loop all the possible direct destination from the current page
    while (it != currentChoice.end()) {
      size_t i = 0;
      //Check if there are different choices with same destination page
      //If yes, skip this choice
      for (i = 0; i < choiceNum - 1; i++) {
        if ((*it)->choiceContent.first == currentChoice[i]->choiceContent.first) {
          break;
        }
      }
      if (i < choiceNum - 1) {
        choiceNum++;
        it++;
        continue;
      }
      else {
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
}

//Invoke dfs to search for success path
void Story::searchSuccessPath() {
  Page * current = pageVec[0];
  std::vector<std::pair<int, int> > path(0);
  dfs(current, path);
}

//Print the successful in correct formaty (Step3)
void Story::printSuccessPath() const {
  if (successPath.size() == 0) {
    std::cout << "This story is unwinnable!\n";
    return;
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
  pageVec.clear();
}

#endif
