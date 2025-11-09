#ifndef SPLINES_SPLINE_H
#define SPLINES_SPLINE_H

#include "common.h"
#include "point.h"

class Spline {
public:
  Spline() = default;
  ~Spline() = default;

  void AddPoint(const Point &_point);
  void RemovePoint();
  void RemovePoint(const std::vector<Point>::iterator &_it);
  void CalculateUnitsPerSample();

  [[nodiscard]]
  Point GetPointOnSpline(float t);

  [[nodiscard]]
  inline const std::vector<Point> &GetPoints() const {
    return points;
  }

  [[nodiscard]]
  inline std::vector<Point> &GetPoints() {
    return points;
  }

  [[nodiscard]]
  inline int32_t GetSampleCount() const {
    return units_per_sample;
  }

  [[nodiscard]]
  inline bool &GetLoopFlag() {
    return closed_loop;
  }

  [[nodiscard]]
  inline float &GetResolution() {
    return resolution;
  }

private:
  std::vector<Point> points;
  int32_t units_per_sample = -1;
  bool closed_loop = false;
  float resolution = 0.00025f;
};

#endif // SPLINES_SPLINE_H
