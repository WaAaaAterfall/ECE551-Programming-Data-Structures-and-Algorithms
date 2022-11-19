#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> test;
  try {
    test.add(4, 20);
    test.remove(4);
    test.add(15, 30);
    std::cout << "Look for Key 15, get value " << test.lookup(15) << std::endl;
    test.add(2, 2);
    test.add(60, 60);
    std::cout << "Look for Key 15, get value " << test.lookup(15) << std::endl;
    test.remove(2);
    std::cout << "Look for Key 2, get value " << test.lookup(2) << std::endl;
    std::cout << "Successful delete\n";
    BstMap<int, int> copytest;
    copytest.add(3, 3);
    copytest = test;
  }
  catch (std::exception & e) {
    std::cerr << e.what();
  }
  return EXIT_SUCCESS;
}
