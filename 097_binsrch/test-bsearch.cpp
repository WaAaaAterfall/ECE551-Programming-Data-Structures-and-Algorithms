#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

//int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int maxInvoke;
  if (high <= low) {
    maxInvoke = 1;
  }
  else {
    maxInvoke = log2(high - low) + 1;
  }
  CountedIntFn * checkFunc = new CountedIntFn(maxInvoke, f, mesg);
  int ans = binarySearchForZero(checkFunc, low, high);
  delete checkFunc;
  if (ans != expected_ans) {
    fprintf(stderr, "Wrong invoke timeon %s \n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main() {
  SinFunction * exampleFunc = new SinFunction();
  check(exampleFunc, 2, 2, 2, "Only one number\n");
  check(exampleFunc, -2, 5, 0, "check 0 between case\n");
  check(exampleFunc, 2, 5, 2, "check all positive case\n");
  check(exampleFunc, -5, -2, -3, "check all negative case\n");
  check(exampleFunc, 0, 5, 0, "check inclusive boundary case\n");
  check(exampleFunc, -5, 0, -1, "check exclusive boundary case\n");
  std::cout << "Corrected implemented\n";
  delete exampleFunc;
  return EXIT_SUCCESS;
}
