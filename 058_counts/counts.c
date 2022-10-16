#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts_array = malloc(sizeof(*counts_array));
  assert(counts_array != NULL);
  counts_array->len = 1;
  counts_array->key_array = malloc(sizeof(counts_array->key_array[0]));
  assert(counts_array->key_array != NULL);
  one_count_t * unknown = malloc(sizeof(*unknown));
  counts_array->key_array[0] = unknown;
  unknown->count = 0;
  char * ch = "<unknown>";
  counts_array->key_array[0]->key = strdup(ch);
  return counts_array;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->key_array[0]->count += 1;
    return;
  }
  for (size_t i = 0; i < c->len; i++) {
    if (strcmp(c->key_array[i]->key, name) == 0) {
      c->key_array[i]->count++;
      return;
    }
  }
  c->len += 1;
  one_count_t ** temp = realloc(c->key_array, c->len * sizeof(c->key_array[0]));
  assert(temp != NULL);
  c->key_array = temp;
  c->key_array[c->len - 1] = malloc(sizeof(*c->key_array[c->len - 1]));
  c->key_array[c->len - 1]->key =
      malloc((strlen(name) + 1) * sizeof(*c->key_array[c->len - 1]->key));
  strcpy(c->key_array[c->len - 1]->key, name);
  c->key_array[c->len - 1]->count = 1;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (c->len == 0) {
    fprintf(stderr, "Weirld, thers is even no  unknown item\n");
    exit(EXIT_FAILURE);
  }

  if (c->len == 1 && c->key_array[0]->count > 0) {
    fprintf(outFile, " %s: %zu\n", c->key_array[0]->key, c->key_array[0]->count);
  }
  else {
    for (size_t i = 1; i < c->len; i++) {
      fprintf(outFile, " %s: %zu\n", c->key_array[i]->key, c->key_array[i]->count);
    }
    if (c->key_array[0]->count > 0) {
      fprintf(outFile, " %s: %zu\n", c->key_array[0]->key, c->key_array[0]->count);
    }
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    free(c->key_array[i]->key);
    free(c->key_array[i]);
  }
  free(c->key_array);
  free(c);
}
