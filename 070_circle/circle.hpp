#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point p, double radius) : center(p), radius(radius) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
