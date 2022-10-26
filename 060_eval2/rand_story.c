#include "rand_story.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(char * errorMessage) {
  fprintf(stderr, "%s\n", errorMessage);
  exit(EXIT_FAILURE);
}

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

char * getCategory(char * str, char * point) {
  char * category = strndup(point + 1, strlen(point + 1) - strlen(str) - 1);
  return category;
}

const char * choosePreviousWord(size_t retrive, usedword_t * usedRecord) {
  if (retrive <= usedRecord->usedCount) {
    size_t index = usedRecord->usedCount - retrive;
    char * word = usedRecord->usedWord[index];
    return word;
  }
  else {
    error("No previous used word could choose");
    return NULL;
  }
}

char * getWord(char * category,
               catarray_t * wordArray,
               usedword_t * usedRecord,
               int mode) {
  size_t retrive = 0;
  if (strlen(category) > 0 && strspn(category, "0123456789") == strlen(category)) {
    retrive = atoi(category);
    char * word = strdup(choosePreviousWord(retrive, usedRecord));
    return word;
  }
  else {
    for (size_t i = 0; i < wordArray->n; i++) {
      char * name = wordArray->arr[i].name;
      if (strcmp(category, name) == 0) {
        const char * w = chooseWord(category, wordArray);
        char * word = strdup(w);
        if (mode == 1) {
          deleteWord(wordArray, i, word);
        }
        return word;
      }
    }
    error("No matched category in wordArray.\n");
    return NULL;
  }
}

char * replaceWithWord(char * replaceRes, size_t resLength, char * word) {
  char * expandWord =
      realloc(replaceRes, (resLength + strlen(word)) * sizeof(*replaceRes));
  strncpy(expandWord + resLength, word, strlen(word));
  return expandWord;
}

usedword_t * updateUseRecord(usedword_t * usedRecord, char * word) {
  char ** newUsedWord =
      realloc(usedRecord->usedWord,
              (usedRecord->usedCount + 1) * sizeof(usedRecord->usedWord[0]));
  newUsedWord[usedRecord->usedCount] = strdup(word);
  usedRecord->usedWord = newUsedWord;
  usedRecord->usedCount++;
  return usedRecord;
}

void deleteWord(catarray_t * wordArray, size_t catIndex, char * word) {
  category_t cat = wordArray->arr[catIndex];
  size_t j = 0;
  for (; j < cat.n_words; j++) {
    if (strcmp(cat.words[j], word) == 0) {
      free(cat.words[j]);
      cat.words[j] = NULL;
      break;
    }
  }
  for (; j < cat.n_words - 1; j++) {
    cat.words[j] = cat.words[j + 1];
  }
  wordArray->arr[catIndex].n_words--;
}

story_t * processTemplate(char * fileName, catarray_t * wordArray, int mode) {
  /* Read File*/
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    error("Cannot open the file");
  }

  /*Initialize the return story*/
  story_t * res = malloc(sizeof(*res));
  res->outputStory = malloc(sizeof(res->outputStory));
  usedword_t * usedRecord = malloc(sizeof(*usedRecord));
  usedRecord->usedCount = 0;
  usedRecord->usedWord = malloc(sizeof(usedRecord->usedWord[0]));
  char * line = NULL;
  size_t sz = 0;
  res->storySize = 0;

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

      str =
          checkValidStory(str);  //The remaining string after the first pair of underscore
      char * category = getCategory(str, point);
      char * word = strdup("cat");
      if (wordArray != NULL) {
        char * selectWord = getWord(category, wordArray, usedRecord, mode);
        free(word);
        word = selectWord;
      }
      replaceRes = replaceWithWord(replaceRes, resLength, word);
      usedRecord = updateUseRecord(usedRecord, word);
      resLength = resLength + strlen(word);
      free(word);
      free(category);
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
  freeUsedWords(usedRecord);
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

int checkValidWord(char * line) {
  if ((strchr(line, ':') == NULL)) {
    return 1;
  }
  else if (strchr(line, '\n') == NULL) {
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
      error("The word file contains line that has no ':' or newline.\n");
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

void freeUsedWords(usedword_t * usedRecord) {
  if (usedRecord != NULL) {
    for (size_t i = 0; i < usedRecord->usedCount; i++) {
      free(usedRecord->usedWord[i]);
    }
    free(usedRecord->usedWord);
    free(usedRecord);
  }
}
