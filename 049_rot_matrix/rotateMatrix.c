#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Useage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  FILE * g = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }
  char row0[11] = {-1};
  char row1[11] = {-1};
  char row2[11] = {-1};
  char row3[11] = {-1};
  char row4[11] = {-1};
  char row5[11] = {-1};
  char row6[11] = {-1};
  char row7[11] = {-1};
  char row8[11] = {-1};
  char row9[11] = {-1};
  char * matrix[10] = {row0, row1, row2, row3, row4, row5, row6, row7, row8, row9};
  char matr[10][12] = {0};
  char revert[10][11] = {0};
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
  c = fgetc(g);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      while (c == '\0' || c == '\n') {
        c = fgetc(g);
      }
      matr[i][j] = c;
      c = fgetc(g);
    }
  }
  //rotate_matrix(matrix, g);
  if (fclose(f) != 0 || fclose(g) != 0) {
    perror("Failed to close the input File");
    return EXIT_FAILURE;
  }
  for (int m = 0; m < 10; m++) {
    for (int n = 0; n < 10; n++) {
      revert[n][9 - m] = matr[m][n];
    }
  }
  for (int p = 0; p < 10; p++) {
    for (int q = 0; q < 10; q++) {
      fprintf(stdout, "%c", revert[p][q]);
    }
    fprintf(stdout, "%c", '\n');
  }
  return EXIT_SUCCESS;
}
