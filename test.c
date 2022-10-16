#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNotIn(char ** record, const char * line, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (strcmp(record[i], line)) {
      return 1;
    }
  }
  return 0;
}
