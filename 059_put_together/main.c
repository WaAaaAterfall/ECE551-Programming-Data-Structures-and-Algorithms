#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file.\n");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  counts_t * count_out = createCounts();
  while (getline(&line, &sz, f) > 0) {
    char * point = line;
    while (*point != '\n') {
      point++;
    }
    *point = '\0';
    addCount(count_out, lookupValue(kvPairs, line));
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Cannot close the file.\n");
    exit(EXIT_FAILURE);
  }
  return count_out;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 2) {
    fprintf(stderr, "Input not enough.\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    char * fileName = argv[i];
    counts_t * c = countFile(fileName, kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(fileName);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Cannot open file!!\n");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Cannot close the file.\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
