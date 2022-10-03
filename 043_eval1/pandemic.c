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
  if (num_pointer == NULL || *num_pointer == '\n') {
    fprintf(stderr, "There is no number for population!");
    exit(EXIT_FAILURE);
  }
  while (*num_pointer != '\n' && num_pointer != NULL) {
    if (isdigit(*num_pointer) == 0) {
      printf("The counry is %s\n", ans.name);
      printf("The wrong char is %s\n.", (num_pointer++));
      fprintf(stderr, "The population in the file is not a number\n");
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
  unsigned total = 0;
  double * record = avg;
  if (n_days <= 7) {
    while (data != NULL) {
      total += *data;
      data++;
    }
    *record = total / (double)n_days;
  }
  else {
    unsigned * first = data;
    unsigned * tail = data;
    unsigned count = 0;
    while (count < 7) {
      total += *tail;
      tail++;
      count++;
    }
    *record = total / 7.0;
    record++;
    while (count < n_days - 1) {
      total -= *first;
      total += *tail;
      first++;
      tail++;
      *record = total / 7.0;
      record++;
      count++;
    }
    total -= *first;
    total += *tail;
    *record = total / 7.0;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  unsigned add = 0;
  size_t count = 0;
  double proportion = 100000 / (double)pop;
  if (n_days == 0) {
    cum = NULL;
    return;
  }
  else if (n_days == 1) {
    *cum = *data * proportion;
    return;
  }
  else {
    while (count < n_days - 1) {
      add += *data;
      *cum = add * proportion;
      cum++;
      count++;
      data++;
    }
    add += *data;
    *cum = add * proportion;
    return;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  for (unsigned j = 0; j < n_days; j++) {
    int country_max = 0;
    unsigned maxRecord = 0;
    for (size_t i = 0; i < n_countries; i++) {
      unsigned * currCountryData = *(data + i);
      if (*(currCountryData + j) > maxRecord) {
        maxRecord = *(currCountryData + j);
        country_max = i;
      }
    }
    country_t country_name = *(countries + country_max);
    printf("%s has the most daily cases with %u\n", country_name.name, maxRecord);
  }
}
