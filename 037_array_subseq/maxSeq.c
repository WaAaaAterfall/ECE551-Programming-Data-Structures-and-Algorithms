#include <stdio.h>
#include <stdlib.h>

size_t check_max(size_t max, size_t count);

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  size_t max = 1;
  size_t count = 1;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i + 1] > array[i]) {
      count++;
    }
    else {
      count = 1;
    }
    if (max < count) {
      max = count;
    }
  }
  return max;
}
