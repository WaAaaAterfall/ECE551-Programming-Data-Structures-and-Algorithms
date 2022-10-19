#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
void Vector2D ::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}

double Vector2D::getMagnitude() const {
  double a = std::pow(x, 2);
  double b = std::pow(y, 2);
  return std::sqrt(a + b);
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D newVec;
  newVec.initVector(this->x + rhs.x, this->y + rhs.y);
  return newVec;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}

double Vector2D ::dot(const Vector2D & rhs) const {
  double res = this->x * rhs.x + this->y * rhs.y;
  return res;
}
void Vector2D::print() const {
  printf("<%.2f, %.2f>", this->x, this->y);
}
