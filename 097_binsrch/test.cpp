#include <cmath>
#include <iostream>

#include "function.h"
class search {
 public:
  bool allNeg = true;
  bool allPos = true;
  int binarySearchForZero(Function<int, int> * f, int low, int high) {
    if (low < high) {
      int i = (high - low) / 2 + low;
      int res = f->invoke(i);
      if (res == 0) {
        return i;
      }
      else if (res < 0) {
        allPos = false;
        return binarySearchForZero(f, i + 1, high);
      }
      else {
        allNeg = false;
        return binarySearchForZero(f, low, i);
      }
    }
    else if (low == high && f->invoke(low) == 0) {
      return low;
    }
    else {
      if (allPos) {
        return low;
      }
      if (allNeg) {
        return high - 1;
      }
      return -1;
    }
  }
};
