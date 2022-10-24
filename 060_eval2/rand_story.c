#include "rand_story.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(char * errorMessage) {
  fprintf(stderr, "%s\n", errorMessage);
  exit(EXIT_FAILURE);
}
//---------------Step1
char * checkValidStory(char * line) {
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
    error("Cannot open the file");
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

    while (strcmp(str, checkValidStory(str)) != 0) {
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
      str = checkValidStory(str);
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
    error("The file cannot be closed.\n");
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

//----------------------Step2
int checkValidWord(char * line) {
  if ((strchr(line, ':') == NULL) && (strchr(line, '\n') == NULL)) {
    return 1;
  }
  else {
    return 0;
  }
}

int checkExistName(catarray_t * wordArray, char * name) {
  for (size_t i = 0; i < wordArray->n; i++) {
    if (strcmp(wordArray->arr[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

catarray_t * readWords(char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    error("Cannot open File.\n");
  }

  catarray_t * wordArray = malloc(sizeof(*wordArray));
  wordArray->arr = malloc(sizeof(wordArray->arr[0]));
  wordArray->n = 0;
  if (wordArray == NULL) {
    error("No enought memory allocation for catArray.\n");
  }
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    if (checkValidWord(line) != 0) {
      error("The word file contains line that has no ':'\n");
    }
    size_t nameSize = 0;
    char * name = malloc(sizeof(*name));
    char * point = line;
    while (*point != ':') {
      name = realloc(name, (nameSize + 1) * sizeof(*name));
      name[nameSize] = *point;
      point++;
      nameSize++;
    }
    name = realloc(name, (nameSize + 1) * sizeof(*name));
    name[nameSize] = '\0';
    char * word = strchr(line, ':') + 1;
    word[strlen(word) - 1] = '\0';
    int index = 0;
    if ((index = checkExistName(wordArray, name)) != -1) {
      wordArray->arr[index].words = realloc(
          wordArray->arr[index].words,
          (wordArray->arr[index].n_words + 1) * sizeof(wordArray->arr[index].words[0]));
      wordArray->arr[index].words[wordArray->arr[index].n_words] = strdup(word);
      wordArray->arr[index].n_words++;
      free(name);
    }
    else {
      wordArray->arr =
          realloc(wordArray->arr, (wordArray->n + 1) * sizeof(wordArray->arr[0]));
      category_t add;
      add.name = name;
      add.n_words = 1;
      add.words = malloc(sizeof(*add.words));
      add.words[0] = strdup(word);
      wordArray->arr[wordArray->n] = add;
      wordArray->n++;
    }
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    error("Cannot close file.\n");
  }
  return wordArray;
}

void printWord(catarray_t * wordArray) {
  for (size_t i = 0; i < wordArray->n; i++) {
    printf("%s:\n", wordArray->arr[i].name);
    for (size_t j = 0; j < wordArray->arr[i].n_words; j++) {
      printf("  %s", wordArray->arr[i].words[j]);
    }
  }
}

void freeCatArray(catarray_t * wordArray) {
  if (wordArray != NULL) {
    for (size_t i = 0; i < wordArray->n; i++) {
      free(wordArray->arr[i].name);
      for (size_t j = 0; j < wordArray->arr[i].n_words; j++) {
        free(wordArray->arr[i].words[j]);
      }
      free(wordArray->arr[i].words);
    }
    free(wordArray->arr);
    free(wordArray);
  }
}
