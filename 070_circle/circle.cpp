#include "circle.hpp"

#include <cmath>
using namespace std;

void Circle::move(double dx, double dy) {
  c.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  const double radius_sum = r + otherCircle.r;
  const double radius_sub = abs(r - otherCircle.r);
  double r_small = r > otherCircle.r ? otherCircle.r : r;
  double r_large = r > otherCircle.r ? r : otherCircle.r;
  const double dis = c.distanceFrom(otherCircle.c);

  if (dis >= radius_sum) {
    return 0.0;
  }
  else if (dis <= radius_sub) {
    return M_PI * r_small * r_small;
  }
  else {
    double a1 =
        acos((r_small * r_small - r_large * r_large + dis * dis) / (2 * dis * r_small));
    double a2 =
        acos((r_large * r_large - r_small * r_small + dis * dis) / (2 * dis * r_large));
    return a1 * r_small * r_small + a2 * r_large * r_large - r_small * dis * sin(a1);
  }
}
