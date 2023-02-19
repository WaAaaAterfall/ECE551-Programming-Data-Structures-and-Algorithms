#ifndef __INT_ARRAY__H__
#define __INT_ARRAY__H__
#include <cstdlib>
#include <ostream>

class IntArray {
 private:
  int * data;
  int arraySize;

 public:
  IntArray();
  IntArray(int t);
  IntArray(const IntArray & rhs);
  IntArray & operator=(const IntArray & rhs);
  ~IntArray();
  int & operator[](int index);
  const int & operator[](int index) const;
  int size() const;
  bool operator==(const IntArray & rhs);
  bool operator!=(const IntArray & rhs);
};

std::ostream & operator<<(std::ostream & s, const IntArray & rhs);
#endif
