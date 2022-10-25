#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
struct story_tag {
  char ** outputStory;
  size_t storySize;
};
typedef struct story_tag story_t;

struct usedword_tag {
  char ** usedWord;
  size_t usedCount;
};
typedef struct usedword_tag usedword_t;

void error(char * errorMessage);

char * checkValidStory(char * line);

story_t * processTemplate(char * fileName, catarray_t * wordArray, int mode);

void printStory(story_t * res);

void freeStory(story_t * res);

//Check if the input word file is legal
int checkValidWord(char * line);
//Check if the name exists in the wordArray
int checkExistName(catarray_t * wordArray, char * name);
// Convert the input word.txt into cataray_t
catarray_t * readWords(char * fileName);
//freecatArray
void freeCatArray(catarray_t * wordArray);

//Export the category from the line, ie. the content between the underscore
char * getCategory(char * str, char * point);
//chooseWord: choose the word from the category from catArray
//choose the word from the previously used words
const char * choosePreviousWord(size_t retrive, usedword_t * usedRecord);
//export the word choosen from either previous used words or the category, catRecord: the previous used words
char * getWord(char * category,
               catarray_t * wordArray,
               usedword_t * usedRecord,
               int mode);
//replace the underscore part with the chosen word and add the word into the catRecord
void replaceWithWord(char * replaceRes,
                     size_t resLength,
                     char * word,
                     usedword_t * usedRecord);

void freeUsedWords(usedword_t * usedRecord);

void deleteWord(catarray_t * wordArray, size_t catIndex, char * word);
#endif
