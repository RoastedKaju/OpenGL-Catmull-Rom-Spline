#include "spline.h"

void Spline::AddPoint(const Point &_point) { points.push_back(_point); }

void Spline::RemovePoint() {
  if (!points.empty()) {
    points.pop_back();
  }
}

void Spline::RemovePoint(const std::vector<Point>::iterator &_it) {
  points.erase(_it);
}

void Spline::CalculateUnitsPerSample() {
  const int n = static_cast<int>(points.size());
  const float resolution = 0.00025f;
  float total_length = 0.0f;

  for (int i = 0; i < n - 1; i++) {
    const Point &p1 = points[i];
    const Point &p2 = points[i + 1];

    total_length += Point::DistanceSquared(p1, p2);
  }

  units_per_sample = static_cast<int32_t>(total_length * resolution);
}

Point Spline::GetPointOnSpline(float t, bool is_closed = false) const {
  // Points size check
  const size_t n = points.size();
  if (n < 2) {
    return {0.0f, 0.0f};
  }

  // Clamp
  t = std::clamp(t, 0.0f, 1.0f);

  // Scale t to segment index
  float segment_count =
      is_closed ? static_cast<float>(n) : static_cast<float>(n - 1);
  float scaledT = t * segment_count;
  int i = static_cast<int>(scaledT);
  float localT = scaledT - static_cast<float>(i);

  // Wrap lambda
  auto wrap = [n](int index) { return (index + n) % static_cast<int>(n); };

  // Clamp indices
  int i0 = is_closed ? wrap(i - 1) : std::max(i - 1, 0);
  int i1 = is_closed ? wrap(i) : i;
  int i2 = is_closed ? wrap(i + 1) : std::min(i + 1, static_cast<int>(n - 1));
  int i3 = is_closed ? wrap(i + 2) : std::min(i + 2, static_cast<int>(n - 1));

  const Point &p0 = points[i0];
  const Point &p1 = points[i1];
  const Point &p2 = points[i2];
  const Point &p3 = points[i3];

  // Catmull-Rom interpolation
  float tt = localT * localT;
  float ttt = tt * localT;

  Point result{0.0f, 0.0f};
  result.x = 0.5f * ((2.0f * p1.x) + (-p0.x + p2.x) * localT +
                     (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * tt +
                     (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * ttt);

  result.y = 0.5f * ((2.0f * p1.y) + (-p0.y + p2.y) * localT +
                     (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * tt +
                     (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * ttt);

  return result;
}