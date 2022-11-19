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
    return binarySearch(f, low, i);
  }
}

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high) {
    return low;
  }
  int l = low;
  int r = high;
  while (l < r) {
    int mid = l + (r - l) / 2;
    int res = f->invoke(mid);
    if (res > 0) {
      r = mid;
    }
    else if (res == 0) {
      return mid;
    }
    else {
      l = mid + 1;
    }
  }
  if (low == l) {
    return low;
  }
  else {
    return r - 1;
  }
}