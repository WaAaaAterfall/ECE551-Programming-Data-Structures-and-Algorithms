#include <stdio.h>
#include <stdlib.h>

size_t check_max(size_t max, size_t count);

size_t isBigger(int val1, int val2, size_t count) {
  if (val2 > val1) {
    count++;
  }
  else {
    count = 1;
  }
  return count;
}

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  size_t max = 1;
  size_t count = 1;
  for (size_t i = 0; i < n - 1; i++) {
    count = isBigger(array[i], array[i + 1], count);
    if (max < count) {
      max = count;
    }
  }
  return max;
}
