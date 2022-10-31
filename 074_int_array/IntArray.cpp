#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), arraySize(0) {
}

IntArray::IntArray(int n) : data(new int[n]), arraySize(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.arraySize]), arraySize(rhs.arraySize) {
  for (int i = 0; i < rhs.arraySize; i++) {
    data[i] = rhs[i];
  }
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.arraySize];
    for (int i = 0; i < rhs.arraySize; i++) {
      temp[i] = rhs[i];
    }
    arraySize = rhs.arraySize;
    delete[] data;
    data = temp;
  }
  return *this;
}

int & IntArray::operator[](int index) {
  assert(index >= 0 && index < arraySize);
  return data[index];
}

const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < arraySize);
  return data[index];
}

int IntArray::size() const {
  return arraySize;
}

bool IntArray::operator==(const IntArray & rhs) {
  if (arraySize != rhs.arraySize) {
    return false;
  }
  for (int i = 0; i < arraySize; i++) {
    if (data[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) {
  return !(*this == rhs);
}

IntArray::~IntArray() {
  delete[] data;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  if (rhs.size() != 0) {
    s << rhs[rhs.size() - 1] << "}";
  }
  else {
    s << "}";
  }
  return s;
}
