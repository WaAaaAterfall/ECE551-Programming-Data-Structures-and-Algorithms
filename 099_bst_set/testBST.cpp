#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include "bstset.h"
#include "set.h"

int main(void) {
  BstSet<int> test;
  try {
    test.add(50);
    test.add(30);
    test.add(20);
    test.add(40);
    test.add(70);
    test.add(60);
    test.add(80);
    test.add(0);
    test.printorder();
    std::cout << "\n";
    std::cout << "Look for Key 20, get value\n " << test.contains(20) << std::endl;
    test.add(0);
    std::cout << "Look for Key 0, get value\n " << test.contains(0) << std::endl;
    BstSet<int> testcopy(test);
    testcopy.printorder();
    std::cout << "\n";
    testcopy.add(100);
    BstSet<int> testtest(test);
    testtest = testcopy;
    testtest.printorder();
    std::cout << "\n";
    test.remove(20);
    test.printorder();
    std::cout << "\n";
    test.remove(30);
    test.printorder();
    std::cout << "\n";
    test.remove(50);
    test.printorder();
    std::cout << "\n";
    std::cout << "Look for Key 2, get value\n " << test.contains(2) << std::endl;
    std::cout << "Look for Key 50, get value\n " << test.contains(50) << std::endl;
    std::cout << "Successful delete\n";
    BstSet<int> copytest(test);
    copytest.add(3);
    copytest = test;
  }
  catch (std::exception & e) {
    std::cerr << e.what();
  }
  return EXIT_SUCCESS;
}
