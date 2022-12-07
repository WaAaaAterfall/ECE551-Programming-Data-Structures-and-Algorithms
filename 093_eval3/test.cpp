#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "Story.hpp"
//#include "Page.hpp"
#include "util.hpp"

int main() {
  assert(checkValidNum("5"));
  assert(checkValidNum("   5"));
  assert(!checkValidNum("5   "));
  assert(!checkValidNum("123abc"));
  assert(!checkValidNum("abc24"));
  std::cout << "Finish Testing.\n";
}

// if (argc != 3) {
//   std::cerr << "Wrong input!\n";
//   return EXIT_FAILURE;
// }

// std::string path = argv[1];
// Story * story = new Story(path);
// story->printStory();
// std::cout << "Initializer Constructor.\n";
// Story testStory(*story);
// testStory.printStory();
// delete story;
// std::cout << "Destructor after initizlizer Constructor.\n";
// testStory.printStory();
// std::string path2 = argv[2];
// Story * story2 = new Story(path2);
// testStory = *story2;
// delete story2;
// std::cout << "Destructor after copy Constructor.\n";
// testStory.printStory();
//}
//   std::string input = "0@N:page0.txt\n";
//   Page * testPage = new Page(input.substr(0, input.size() - 1), "");
//   std::cout << input.substr(0, input.size() - 1);
//   testPage->addChoices("0:2:Choose the magic whistle.\n", 2);
//   testPage->addChoices("0:3:Choose the magic shoes.\n", 2);
//   testPage->addChoices("0:4:Choose the magic toaster.\n", 2);
//   testPage->printPage();
//   std::string input2 = "1@N:page1.txt\n";
//   Page testPage2(*testPage);
//   std::cout << "Initialier constuctor\n";
//   testPage2.printPage();
//   testPage2.addChoices("0:10:I am not gonna choose anything!.\n", 2);
//   delete testPage;
//   std::cout << "destroctor\n";
//   //testPage->printPage();
//   testPage2.printPage();
//   Page testPage3("1@N:page1.txt", "");
//   testPage3.addChoices("0:10:I am not gonna choose anything!.\n", 2);
//   testPage2 = testPage3;
//   std::cout << "copy constuctor\n";
//   testPage2.printPage();
//   Page * testPage4 = new Page(input.substr(0, input.size() - 1), "");
//   testPage4->addChoices("0:2:Choose the magic whistle.\n", 2);
//   testPage4->addChoices("0:3:Choose the magic shoes.\n", 2);
//   testPage2 = *testPage4;
//   testPage2.printPage();
//   delete testPage4;
//   std::cout << "Destructor after copy constuctor\n";
//   testPage2.printPage();
// }
