#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input command.");
    exit(EXIT_FAILURE);
  }

  char * fileName = argv[1];
}
