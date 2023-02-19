#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t max) {
  if (maxSeq(array, n) != max) {
    printf("test failed\n");
    exit(EXIT_FAILURE);
  }
  else {
    printf("passed!\n");
  }
}

int main(void) {
  int array1[] = {1, 2, 3, 4, 5};
  run_check(array1, 5, 5);
  int array2[] = {2, 1, 3};
  run_check(array2, 3, 2);

  int array3[] = {0};
  run_check(array3, 1, 1);

  run_check(NULL, 0, 0);

  int array5[] = {3, 2, 1};
  run_check(array5, 3, 1);

  int array6[] = {1, 1, 1};
  run_check(array6, 3, 1);

  int array7[] = {-1, 2, 3, -2, -1};
  run_check(array7, 5, 3);

  return EXIT_SUCCESS;
}
