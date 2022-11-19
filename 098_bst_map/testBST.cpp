#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> test;
  try {
    test.add(50, 20);
    test.add(30, 20);
    test.add(20, 30);
    test.add(40, 20);
    test.add(70, 40);
    test.add(60, 20);
    test.add(80, 20);
    test.add(0, 20);
    test.printorder();
    std::cout << "\n";
    std::cout << "Look for Key 20, get value\n " << test.lookup(20) << std::endl;
    test.add(0, 60);
    std::cout << "Look for Key 0, get value\n " << test.lookup(0) << std::endl;
    test.remove(20);
    test.printorder();
    std::cout << "\n";
    test.remove(30);
    test.printorder();
    std::cout << "\n";
    test.remove(50);
    test.printorder();
    std::cout << "\n";
    std::cout << "Look for Key 2, get value\n " << test.lookup(2) << std::endl;
    std::cout << "Look for Key 50, get value\n " << test.lookup(50) << std::endl;
    std::cout << "Successful delete\n";
    BstMap<int, int> copytest(test);
    copytest.add(3, 3);
    copytest = test;
  }
  catch (std::exception & e) {
    std::cerr << e.what();
  }
  return EXIT_SUCCESS;
}
