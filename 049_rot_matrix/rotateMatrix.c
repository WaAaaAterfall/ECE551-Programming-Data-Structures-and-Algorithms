#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate_matrix(char ** matrix, FILE * f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
          char * row = matrix[j];
          row[i] = c;
        }
      }
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Useage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  if (argv[1] == NULL) {
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }
  char * matrix[10];
  int c;
  int row_count = 0;
  int line_count = 0;
  while ((c = fgetc(f)) != EOF) {
    if ((int)c == 255) {
      fprintf(stderr, "The file contains illegal input char.\n");
      return EXIT_FAILURE;
    }
    if (line_count > 10) {
      fprintf(stderr, "The num of lines is larger than 10.\n");
      return EXIT_FAILURE;
    }
    if (c == '\n') {
      if (line_count != 10) {
        if (row_count != 10) {
          fprintf(stderr, "The number of elements in each row is not 10.\n");
          return EXIT_FAILURE;
        }
      }
      line_count++;
      row_count = 0;
    }
    else {
      row_count++;
    }
  }
  if (line_count < 10) {
    fprintf(stderr, "The num of lines is smaller than 10.\n");
    return EXIT_FAILURE;
  }
  rotate_matrix(matrix, f);
  for (int i = 0; i < 10; i++) {
    char * line = matrix[i];
    for (int j = 0; j < 10; j++) {
      printf("%c", line[j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
