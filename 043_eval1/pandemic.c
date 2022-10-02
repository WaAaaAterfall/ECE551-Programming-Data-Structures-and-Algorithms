#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  char * point = line;
  const char * split = ",";
  int count = 0;
  char * name = ans.name;
  while (*point != ',') {
    count++;
    char current_char = *point;
    *name = current_char;
    name++;
    point++;
  }
  *name = '\0';
  strsep(&point, split);
  while (*point == ' ') {
    point++;
  }
  char * num_pointer = point;
  printf("The char of the population %s\n", num_pointer);
  if (num_pointer == NULL || *num_pointer == '\n') {
    printf("There is no number for population!");
    exit(EXIT_FAILURE);
  }
  while (*num_pointer != '\n' && num_pointer != NULL) {
    if (isdigit(*num_pointer) == 0) {
      printf("The counry is %s\n", ans.name);
      printf("The wrong char is %s\n.", (num_pointer++));
      printf("The population in the file is not a number\n");
      exit(EXIT_FAILURE);
    }
    num_pointer++;
  }
  int population = atoi(point);
  ans.population = population;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
