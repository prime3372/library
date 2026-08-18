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
  friend point operator/(long double lhs, const point& rhs) {
    return point(rhs) /= lhs;
  }

  long double dot(const point& rhs) const { return x * rhs.x + y * rhs.y; }
  long double cross(const point& rhs) const { return x * rhs.y - y * rhs.x; }

  long double norm2() const { return x * x + y * y; }
  long double norm() const { return std::sqrt(x * x + y * y); }
  point normalize() const { return *this / norm(); }

  point rot() const { return point(y, -x); }

  friend bool operator==(const point& lhs, const point& rhs) {
    return std::abs(lhs.x - rhs.x) < eps && std::abs(lhs.y - rhs.y) < eps;
  }
  friend bool operator!=(const point& lhs, const point& rhs) {
    return !(lhs == rhs);
  }

  friend std::istream& operator>>(std::istream& is, point& v) {
    return is >> v.x >> v.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const point& v) {
    return os << v.x << " " << v.y;
  }

 private:
  static constexpr long double eps = 1e-9;
};

}  // namespace cp