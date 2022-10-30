#include "circle.hpp"

#include <cmath>

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = this->center.distanceFrom(otherCircle.center);
  double radiusSum = this->radius + otherCircle.radius;
  double radiusSub = std::abs(this->radius - otherCircle.radius);
  if (distance >= radiusSum) {
    return 0;
  }
  else {
    double biggerR = this->radius;
    double smallerR = otherCircle.radius;
    if (biggerR <= smallerR) {
      double temp = biggerR;
      biggerR = smallerR;
      smallerR = temp;
    }
    if (distance <= radiusSub) {
      return M_PI * smallerR * smallerR;
    }
    double part1 =
        std::acos((distance * distance + smallerR * smallerR - biggerR * biggerR) /
                  (2 * distance * smallerR));
    double part2 =
        std::acos((distance * distance + biggerR * biggerR - smallerR * smallerR) /
                  (2 * distance * biggerR));
    double part3 = smallerR * smallerR * part1 + biggerR * biggerR * part2 -
                   smallerR * distance * std::sin(part1);
    return part3;
  }
}
