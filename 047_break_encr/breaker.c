#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int getLetterI(double * count, int sum) {
  double maxFreq = 0;
  int indexOfMostFre = 0;
  for (int i = 0; i < 26; i++) {
    count[i] = count[i] / sum;
    if (count[i] > maxFreq) {
      maxFreq = count[i];
      indexOfMostFre = i;
    }
  }
  return indexOfMostFre;
}

void calculate_count(int * count, double * record, FILE * f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      (*count)++;
      int index = (int)c;
      record[index - 97]++;
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Useage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  double count_record[26] = {0};
  int count = 0;
  int * c = &count;
  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }
  calculate_count(c, count_record, f);
  if (count == 0) {
    printf("Empty File\n");
    printf("%d\n", 0);
  }
  else {
    int indexOfMostFre = getLetterI(count_record, count);
    int res = indexOfMostFre - 4;
    if (res < 0) {
      res += 26;
    }
    printf("%d", res);
    if (fclose(f) != 0) {
      perror("Failed to closse the input File!");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
