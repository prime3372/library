#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

namespace cp {

class point {
 public:
  long double x, y;
  point() : x(0), y(0) {}
  point(long double _x, long double _y) : x(_x), y(_y) {}

  point operator+() const { return *this; }
  point operator-() const { return point(-x, -y); }

  point& operator+=(const point& v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  point& operator-=(const point& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  point& operator*=(long double s) {
    x *= s;
    y *= s;
    return *this;
  }
  point& operator/=(long double s) {
    x /= s;
    y /= s;
    return *this;
  }

  friend point operator+(const point& lhs, const point& rhs) {
    return point(lhs) += rhs;
  }
  friend point operator-(const point& lhs, const point& rhs) {
    return point(lhs) -= rhs;
  }
  friend point operator*(const point& lhs, long double rhs) {
    return point(lhs) *= rhs;
  }
  friend point operator*(long double lhs, const point& rhs) {
    return point(rhs) *= lhs;
  }
  friend point operator/(const point& lhs, long double rhs) {
    return point(lhs) /= rhs;
  }

  long double norm() const { return std::sqrt(x * x + y * y); }
  long double norm2() const { return x * x + y * y; }
  point normalize() const { return *this / norm(); }

  point rot() const { return point(y, -x); }

  friend std::istream& operator>>(std::istream& is, point& v) {
    return is >> v.x >> v.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const point& v) {
    return os << v.x << " " << v.y;
  }
};

long double dot(const point& lhs, const point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
long double cross(const point& lhs, const point& rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

}  // namespace cp