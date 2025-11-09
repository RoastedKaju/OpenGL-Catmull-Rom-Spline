#ifndef SPLINES_POINT_H
#define SPLINES_POINT_H

struct Point {
  float x;
  float y;

  Point(const float _x, const float _y) : x{_x}, y{_y} {}

  // Add operator
  Point operator+(const Point other) const {
    return {x + other.x, y + other.y};
  }

  // Subtract operator
  Point operator-(const Point other) const {
    return {x - other.x, y - other.y};
  }

  static float DistanceSquared(const Point& P1, const Point& P2) {
    const float result = std::pow(P1.x - P2.x, 2) + std::pow(P1.y - P2.y, 2);
    return result;
  }
};

#endif // SPLINES_POINT_H
