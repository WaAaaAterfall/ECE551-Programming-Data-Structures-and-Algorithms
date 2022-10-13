#include "kv.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * writePairFromFile(char * line) {
  kvpair_t * pair = malloc(sizeof(*pair));
  char * point = line;
  char * end = line;
  point = strchr(point, '=');
  if (point == NULL) {
    fprintf(stderr, "There is no delimiter in the string.\n");
    exit(EXIT_FAILURE);
  }
  size_t length_key = point - line + 1;
  pair->key = malloc(length_key * sizeof(*pair->key));
  strncpy(pair->key, line, length_key - 1);
  pair->key[length_key - 1] = '\0';

  end = strchr(line, '\n');
  size_t length_value = end - point;
  pair->value = malloc(length_value * sizeof(*pair->value));
  strncpy(pair->value, point + 1, length_value - 1);
  pair->value[length_value - 1] = '\0';

  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * res = malloc(sizeof(*res));
  res->len = 0;
  res->pair = NULL;
  if (res == NULL) {
    fprintf(stderr, "No enough memoryspace!\n");
    exit(EXIT_FAILURE);
  }
  res->len = 0;
  res->pair = malloc(sizeof(res->pair[0]));
  if (res->pair == NULL) {
    fprintf(stderr, "No enough memory space.\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file\n");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t lineCount = 0;
  while (getline(&line, &lineCount, f) >= 0) {
    res->len++;
    res->pair = realloc(res->pair, (res->len) * sizeof(*(res->pair)));
    res->pair[res->len - 1] = writePairFromFile(line);
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "The file cannot be closed.\n");
    exit(EXIT_FAILURE);
  }
  return res;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t i = 0;
  while (i < pairs->len) {
    free((pairs->pair[i])->key);
    free((pairs->pair[i])->value);
    free(pairs->pair[i]);
    i++;
  }
  free(pairs->pair);
  free(pairs);
}
void printKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t i = 0;
  while (i < pairs->len) {
    printf("key = %s, value = %s \n", (pairs->pair[i])->key, (pairs->pair[i])->value);
    i++;
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    if (!strcmp((pairs->pair[i])->key, key)) {
      return (pairs->pair[i])->value;
    }
  }
  return NULL;
}
