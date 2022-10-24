#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    error("Wrong input command.");
  }

  char * fileWords = argv[1];
  char * fileStory = argv[2];

  catarray_t * wordArray = readWords(fileWords);
  //printWords(wordArray);
  story_t * storyOut = processTemplate(fileStory, wordArray);
  printStory(storyOut);
  freeCatArray(wordArray);
  freeStory(storyOut);
}
