//This c file is the first step of the project, the step which parses the story template
#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  /*check the input argument is right.*/
  if (argc != 2) {
    fprintf(stderr, "Wrong input argument number.");
    exit(EXIT_FAILURE);
  }
  catarray_t * wordArray = NULL;
  /*Check wether the input story template is legal, return any possible error, otherwise return the index of each left underscore shown up. Replace each underscore zone with "cat"*/
  story_t * res = processTemplate(argv[1], wordArray, 0);
  /*print out the result*/
  printStory(res);
  freeStory(res);
}
