#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * res = new uint64_t[257]();
  for (size_t i = 0; i < 257; i++) {
    res[i] = 0;
  }
  std::ifstream f;
  f.open(fname);
  if (!f.is_open()) {
    std::cerr << "Cannot open the file";
    exit(EXIT_FAILURE);
  }
  int num;
  while ((num = f.get()) != EOF) {
    res[num]++;
  }
  res[256]++;
  f.close();
  return res;
}
