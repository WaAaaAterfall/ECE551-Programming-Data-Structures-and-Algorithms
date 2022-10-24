#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    error("Wrong input command.");
  }

  char * fileName = argv[1];
  catarray_t * wordArray = readWords(fileName);
  printWords(wordArray);
  freeCatArray(wordArray);
}
