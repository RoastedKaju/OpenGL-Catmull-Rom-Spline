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
};

#endif // SPLINES_POINT_H
