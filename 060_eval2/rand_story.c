#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * checkValid(char * line) {
  char * underscore1 = strchr(line, '_');
  if (underscore1 == NULL) {
    return line;
  }
  else {
    char * underscore2 = strchr((underscore1 + 1), '_');
    if (underscore2 == NULL) {
      fprintf(stderr, "Underscore in the template cannot be paired.\n");
      exit(EXIT_FAILURE);
    }
    else {
      return underscore2 + 1;
    }
  }
}

story_t * processValidTemplate(char * fileName) {
  /* Read File*/
  char * word = "cat";
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file");
    exit(EXIT_FAILURE);
  }

  /*Initialize the return story*/
  story_t * res = malloc(sizeof(*res));
  res->outputStory = malloc(sizeof(res->outputStory));
  //why can't I use char outputStory = res->outputstory
  char * line = NULL;
  res->storySize = 0;
  size_t sz = 0;

  /*Check the input line by line*/
  while ((getline(&line, &sz, f)) >= 0) {
    char * replaceRes = malloc(sizeof(*replaceRes));
    char * str = line;
    size_t resLength = 0;

    while (strcmp(str, checkValid(str)) != 0) {
      //if the remaining string contains paired underscore
      char * point = str;
      while (*point != '_') {
        replaceRes = realloc(replaceRes, (resLength + 1) * sizeof(*replaceRes));
        replaceRes[resLength] = *point;
        resLength++;
        point++;
      }
      replaceRes = realloc(replaceRes, (resLength + 3) * sizeof(*replaceRes));
      strncpy(replaceRes + resLength, word, strlen(word));
      resLength = resLength + 3;
      str = checkValid(str);
    }
    if (str != NULL) {
      replaceRes =
          realloc(replaceRes, (resLength + strlen(str) + 1) * sizeof(*replaceRes));
      strncpy(replaceRes + resLength, str, strlen(str) + 1);
    }
    else {
      replaceRes = realloc(replaceRes, (resLength + 1) * sizeof(*replaceRes));
      replaceRes[resLength] = '\0';
    }
    free(line);
    line = NULL;
    res->outputStory =
        realloc(res->outputStory, (res->storySize + 1) * sizeof(*res->outputStory));
    res->outputStory[res->storySize] = replaceRes;
    res->storySize++;
  }
  free(line);
  line = NULL;
  if (fclose(f) != 0) {
    fprintf(stderr, "The file cannot be closed.\n");
    exit(EXIT_FAILURE);
  }
  return res;
}

void printStory(story_t * res) {
  for (size_t i = 0; i < res->storySize; i++) {
    printf("%s", res->outputStory[i]);
  }
}

void freeStory(story_t * res) {
  for (size_t i = 0; i < res->storySize; i++) {
    free(res->outputStory[i]);
  }
  free(res->outputStory);
  free(res);
}
