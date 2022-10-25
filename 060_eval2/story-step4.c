#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

void processStory(char * fileWords, char * fileStory, int mode) {
  catarray_t * wordArray = readWords(fileWords);
  //  printWords(wordArray);
  story_t * storyOut = processTemplate(fileStory, wordArray, mode);
  printStory(storyOut);
  freeCatArray(wordArray);
  freeStory(storyOut);
}

int main(int argc, char ** argv) {
  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      error("Wrong optional input!");
    }
    char * fileWords = argv[2];
    char * fileStory = argv[3];
    processStory(fileWords, fileStory, 1);
  }
  else if (argc == 3) {
    char * fileWords = argv[1];
    char * fileStory = argv[2];
    processStory(fileWords, fileStory, 0);
  }
  else {
    error("Wrong number of input commands");
  }
  return EXIT_SUCCESS;
}
