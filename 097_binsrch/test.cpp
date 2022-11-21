#include <cmath>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  bool allNeg = true;
  bool allPos = true;
  for (int i = low; i < high; i++) {
    int res = f->invoke(i);
    if (res == 0) {
      return i;
    }
    else if (res < 0) {
      allPos = false;
    }
    else {
      allNeg = false;
    }
  }
  if (allPos) {
    return low;
  }
  if (allNeg) {
    return high - 1;
  }
  return -1;
}
