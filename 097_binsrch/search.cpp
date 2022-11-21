#include <cmath>
#include <iostream>

#include "function.h"

int binarySearch(Function<int, int> * f, int low, int high) {
  if (low == high) {
    int value = f->invoke(low);
    std::cout << "Invoke1\n";
    if (value >= 0) {
      return low;
    }
    else {
      return high;
    }
  }
  int i = (high - low) / 2 + low;
  std::cout << "Invoke2\n";
  int res = f->invoke(i);
  if (res == 0) {
    return i;
  }
  else if (res < 0) {
    return binarySearch(f, i + 1, high);
  }
  else {
    return binarySearch(f, low, i - 1);
  }
}

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high) {
    exit(EXIT_FAILURE);
  }
  else if (low == high) {
    return low;
  }
  else {
    int ans = binarySearch(f, low, high - 1);
    return ans;
  }
}
