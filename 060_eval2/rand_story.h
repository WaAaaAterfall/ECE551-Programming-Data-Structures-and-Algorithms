#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

//struct for storing finished story
struct story_tag {
  char ** outputStory;
  size_t storySize;
};
typedef struct story_tag story_t;

//struct for storing usedWord for backreferencing
struct usedword_tag {
  char ** usedWord;
  size_t usedCount;
};
typedef struct usedword_tag usedword_t;

//print any errormessage
void error(char * errorMessage);

//check if the line is valid for a story (i.e. paired underscore)
char * checkValidStory(char * line);

//process the story and return the finished story
story_t * processTemplate(char * fileName, catarray_t * wordArray, int mode);

//print the finished story to stdout
void printStory(story_t * res);

//free the story from memory
void freeStory(story_t * res);

//Check if the input word file is legal (i.e. colon)
int checkValidWord(char * line);

//Check if the category(name) exists in the wordArray
int checkExistName(catarray_t * wordArray, char * name);

// Convert the input word.txt into cataray_t
catarray_t * readWords(char * fileName);

//free catArray from memory
void freeCatArray(catarray_t * wordArray);

//Export the category from the line, ie. the content between the underscore
char * getCategory(char * str, char * point);

//chooseWord: choose the word from the category from catArray, in provided

//choose the word from the previously used words
const char * choosePreviousWord(size_t retrive, usedword_t * usedRecord);

//export the word choosen from either previous used words or the catarray, catRecord: the previous used words
char * getWord(char * category,
               catarray_t * wordArray,
               usedword_t * usedRecord,
               int mode);

//replace the underscore part with the chosen word and add the word into the catRecord
char * replaceWithWord(char * replaceRes, size_t resLength, char * word);

//update the backreference word list
usedword_t * updateUsedRecord(usedword_t * usedRecord, char * word);

//free the backreferencing word list from memory
void freeUsedWords(usedword_t * usedRecord);

//for step 4, delete any used word from the catarray
void deleteWord(catarray_t * wordArray, size_t catIndex, char * word);
#endif
