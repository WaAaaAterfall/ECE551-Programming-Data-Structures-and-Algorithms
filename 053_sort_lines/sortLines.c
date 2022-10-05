#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printData(char ** record, size_t lineCount) {
  size_t i = 0;
  while (i < lineCount) {
    printf("%s", record[i]);
    free(record[i]);
    i++;
  }
}

void sortFile(FILE * f) {
  size_t countChar = 0;
  size_t countLine = 0;
  char ** record = NULL;
  record = malloc(sizeof(*record));
  char * line = NULL;
  while (getline(&line, &countChar, f) >= 0) {
    countLine++;
    record = realloc(record, (countLine) * sizeof(*record));
    *(record + (countLine - 1)) = line;
    line = NULL;
  }
  free(line);
  sortData(record, countLine);
  printData(record, countLine);
  free(record);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      perror("Could not open file\n");
      return EXIT_FAILURE;
    }
    sortFile(f);
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Cannot open file!\n");
        return EXIT_FAILURE;
      }
      sortFile(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "File to close the input file\n");
        return EXIT_FAILURE;
      }
    }
  }
  else {
    fprintf(stderr, "Wrong argc\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
