#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned num, unsigned order) {
  if (order == 0) {
    return 1;
  }
  else {
    return num * power(num, order - 1);
  }
}
