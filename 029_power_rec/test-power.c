#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);  //prototype of power function

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("test for x = %u,y = %u failed\n", x, y);
    exit(EXIT_FAILURE);
  }
  else {
    printf("the value is expected\n");
  }
}

int main() {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  // run_check(3, 'a', 0);
  run_check(2, 3, 8);
  run_check(1000, 2, 1000000);
  run_check(1, 0, 1);
  run_check(1, 1, 1);
  return EXIT_SUCCESS;
}
