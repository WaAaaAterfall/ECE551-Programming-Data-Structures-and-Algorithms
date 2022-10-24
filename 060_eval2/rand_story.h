#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
struct story_tag {
  char ** outputStory;
  size_t storySize;
};
typedef struct story_tag story_t;

void error(char * errorMessage);

char * checkValidStory(char * line);

story_t * processValidTemplate(char * fileName);

void printStory(story_t * res);

void freeStory(story_t * res);

//------Step 2
//Check if the input word file is legal
int checkValidWord(char * line);
//Check if the name exists in the wordArray
int checkExistName(catarray_t * wordArray, char * name);
// Convert the input word.txt into cataray_t
catarray_t * readWords(char * fileName);
//freecatArray
void freeCatArray(catarray_t * wordArray);
#endif
