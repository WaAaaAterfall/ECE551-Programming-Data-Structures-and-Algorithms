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
  //check if there is underscorein the line. If there is, check if it is paired
  //return the story after the second underscore
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
  //check wether the backreference exceeds
  if (retrive <= usedRecord->usedCount) {
    size_t index = usedRecord->usedCount - retrive;
    char * word = usedRecord->usedWord[index];
    return word;
  }
  //exceeds, return error
  else {
    error("No previous used word to choose");
    return NULL;
  }
}

char * getWord(char * category,
               catarray_t * wordArray,
               usedword_t * usedRecord,
               int mode) {
  size_t retrive = 0;
  char * categoryTrim = category;
  //for accommodating step 1
  if (wordArray == NULL) {
    char * cat = strdup(chooseWord(category, wordArray));
    return cat;
  }
  //omit the blank before positive number
  while (*categoryTrim == ' ') {
    categoryTrim++;
  }
  if (strlen(categoryTrim) > 0 &&
      strspn(categoryTrim, "0123456789") == strlen(categoryTrim)) {
    retrive = atoi(categoryTrim);
    if (retrive > 0) {  //check if it is an appropriate backreference
      char * word = strdup(choosePreviousWord(retrive, usedRecord));
      return word;
    }
  }
  //If it is not a back reference, find the word in cat array
  for (size_t i = 0; i < wordArray->n; i++) {
    char * name = wordArray->arr[i].name;
    if (strcmp(category, name) == 0) {
      //find the matching cateory
      const char * w = chooseWord(category, wordArray);
      char * word = strdup(w);
      if (mode == 1) {  //if there is "-n", delete the word in catarray
        deleteWord(wordArray, i, word);
      }
      return word;
    }
  }
  error("No matched category in wordArray.\n");
  return NULL;
}

char * replaceWithWord(char * replaceRes, size_t resLength, char * word) {
  char * expandWord =
      realloc(replaceRes, (resLength + strlen(word)) * sizeof(*replaceRes));
  strncpy(expandWord + resLength, word, strlen(word));
  //return the new address of the finished story after realloc
  return expandWord;
}

usedword_t * updateUseRecord(usedword_t * usedRecord, char * word) {
  char ** newUsedWord =
      realloc(usedRecord->usedWord,
              (usedRecord->usedCount + 1) * sizeof(usedRecord->usedWord[0]));
  newUsedWord[usedRecord->usedCount] = strdup(word);
  usedRecord->usedWord = newUsedWord;
  usedRecord->usedCount++;
  //return the updated usedWord
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
  //Because for each words, it stores the address of the bext words, so there is no need to free the last words in the array. They will all be freed at last.
  wordArray->arr[catIndex].n_words--;
}

story_t * processTemplate(char * fileName, catarray_t * wordArray, int mode) {
  /* Read File*/
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    error("Cannot open the file");
  }

  /*Initialize the return story and the backreference list*/
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
      //First, copy the content not in the blank in the finished story
      while (*point != '_') {
        replaceRes = realloc(replaceRes, (resLength + 1) * sizeof(*replaceRes));
        replaceRes[resLength] = *point;
        resLength++;
        point++;
      }
      //"point" points to the first underscore
      //Get the remaining string after a pair of underscore
      str = checkValidStory(str);

      //Second, read the category in the blank and choose the appropriate words that can write in the finished story
      //get the content of category
      char * category = getCategory(str, point);
      //get the word in this category
      char * word = getWord(category, wordArray, usedRecord, mode);
      //write the word into the story
      replaceRes = replaceWithWord(replaceRes, resLength, word);
      //update backreference struct
      usedRecord = updateUseRecord(usedRecord, word);
      //update the length of finished story of current line
      resLength = resLength + strlen(word);
      free(word);
      free(category);
    }
    //Third, loop throught all the underscore in the line.
    //Forth, if there is no more underscore, put all the remains in the finished story
    if (str != NULL) {  //story remaining
      replaceRes =
          realloc(replaceRes, (resLength + strlen(str) + 1) * sizeof(*replaceRes));
      strncpy(replaceRes + resLength, str, strlen(str) + 1);
    }
    else {  //no story remains
      replaceRes = realloc(replaceRes, (resLength + 1) * sizeof(*replaceRes));
      replaceRes[resLength] = '\0';
    }

    free(line);
    line = NULL;
    //put the finished story line in the res
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
    fprintf(stdout, "%s", res->outputStory[i]);
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
  //check if there is one colons in this line
  if ((strchr(line, ':') == NULL)) {
    return 1;
  }
  else if (strchr(line, '\n') == NULL) {
    return 1;
  }
  else {
    //illegal word doc
    return 0;
  }
}

int checkExistName(catarray_t * wordArray, char * name) {
  for (size_t i = 0; i < wordArray->n; i++) {
    if (strcmp(wordArray->arr[i].name, name) == 0) {
      //return the index of this category for further operation
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
    //if the line is legal:
    size_t nameSize = 0;
    char * name = malloc(sizeof(*name));
    char * point = line;
    //extract the category(name)
    while (*point != ':') {
      name = realloc(name, (nameSize + 1) * sizeof(*name));
      name[nameSize] = *point;
      point++;
      nameSize++;
    }
    name = realloc(name, (nameSize + 1) * sizeof(*name));
    name[nameSize] = '\0';
    //extract the word after colon
    char * word = strchr(line, ':') + 1;
    word[strlen(word) - 1] = '\0';
    int index = 0;
    if ((index = checkExistName(wordArray, name)) != -1) {
      //if this catrgory already exists
      wordArray->arr[index].words = realloc(
          wordArray->arr[index].words,
          (wordArray->arr[index].n_words + 1) * sizeof(wordArray->arr[index].words[0]));
      wordArray->arr[index].words[wordArray->arr[index].n_words] = strdup(word);
      wordArray->arr[index].n_words++;
      free(name);
    }
    else {
      //if it ia new category
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
