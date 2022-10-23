#ifndef __PROVIDED_H__
#define __PROVIDED_H__

#include <stdlib.h>

struct category_tag {
  char * name;
  char ** words;
  size_t n_words;
};
typedef struct category_tag category_t;

struct catarray_tag {
  category_t * arr;
  size_t n;
};
typedef struct catarray_tag catarray_t;

struct story_tag {
  char ** outputStory;
  size_t storySize;
};
typedef struct story_tag story_t;

story_t * processValidTemplate(char * fileName);

void printStory(story_t * res);

void freeStory(story_t * res);
const char * chooseWord(char * category, catarray_t * cats);
void printWords(catarray_t * cats);

#endif
