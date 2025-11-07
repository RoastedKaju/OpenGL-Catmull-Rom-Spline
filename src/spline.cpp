#include "spline.h"

Spline::Spline() {}

Spline::~Spline() {}

void Spline::AddPoint(const Point &_point) { points.push_back(_point); }

void Spline::RemovePoint() {
  if (!points.empty()) {
    points.pop_back();
  }
}
void Spline::RemovePoint(const std::vector<Point>::iterator &_it) {
  points.erase(_it);
}