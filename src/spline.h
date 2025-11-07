#ifndef SPLINES_SPLINE_H
#define SPLINES_SPLINE_H

#include "common.h"
#include "point.h"

class Spline {
public:
  Spline();
  ~Spline();

  void AddPoint(const Point &_point);
  void RemovePoint();
  void RemovePoint(const std::vector<Point>::iterator &_it);

  [[nodiscard]]
  inline const std::vector<Point> &GetPoints() const { return points; }
  [[nodiscard]]
  inline std::vector<Point>& GetPoints() { return points;}

private:
  std::vector<Point> points;
};

#endif // SPLINES_SPLINE_H
