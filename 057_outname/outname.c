#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * point = inputName;
  int count = 0;
  if (inputName != NULL) {
    while (*point != '\0') {
      point++;
      count++;
    }
  }
  char * outname = malloc((count + 8) * sizeof(*outname));
  for (int i = 0; i < count; i++) {
    outname[i] = inputName[i];
  }
  char * concate = ".counts";
  for (int j = 0; j < 7; j++) {
    outname[count + j] = concate[j];
  }
  outname[count + 7] = '\0';
  return outname;
}
