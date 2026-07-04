#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

namespace cp {

struct point {
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

  friend point operator+(const point& lhs, const point& rhs) { return point(lhs) += rhs; }
  friend point operator-(const point& lhs, const point& rhs) { return point(lhs) -= rhs; }
  friend point operator*(const point& lhs, long double rhs) { return point(lhs) *= rhs; }
  friend point operator*(long double lhs, const point& rhs) { return point(rhs) *= lhs; }
  friend point operator/(const point& lhs, long double rhs) { return point(lhs) /= rhs; }
  friend point operator/(double lhs, const point& rhs) { return point(rhs) /= lhs; }

  long double dot(const point& rhs) const { return x * rhs.x + y * rhs. y; }

  long double cross(const point& rhs) const { return x * rhs.y - y * rhs.x; }

  long double norm2() const { return x * x + y * y;}

  long double norm() const { return std::sqrt(x * x + y * y);}

  point normalize() const { return *this / norm();}

  point rot() const { return point(y, -x);}
  point rot(int n) const {
    n = n < 0 ? n % 4 + 4 : n % 4;
    if (n == 0) return *this;
    if (n == 1) return rot();
    if (n == 2) return -*this;
    return -rot();
  }
  
  int ort() const {
    if (std::abs(x) < eps && std::abs(y) < eps) return 0;
    if (y < 0) return x < 0 ? -2 : -1;
    return x < 0 ? 2 : 1;
  }

  friend bool operator==(const point& lhs, const point& rhs) {
    return std::abs(lhs.x - rhs.x) < eps && std::abs(lhs.y - rhs.y) < eps;
  }
  friend bool operator!=(const point& lhs, const point& rhs) { return !(lhs == rhs); }

  friend int argcmp(const point& lhs, const point& rhs) {
    int lo = lhs.ort(), ro = rhs.ort();
    if (lo != ro) return lo < ro ? -1 : 1;
    return lhs.cross(rhs) > eps ? -1 : lhs.cross(rhs) < eps ? 1 : 0;
  }
  friend bool operator<(const point& lhs, const point& rhs) { return argcmp(lhs, rhs) < 0; }
  friend bool operator>(const point& lhs, const point& rhs) { return argcmp(lhs, rhs) > 0; }
  
  friend std::istream& operator>>(std::istream& is, point& v) {
    return is >> v.x >> v.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const point& v) {
    return os << v.x << " " << v.y;
  }
  
private:
  static constexpr long double eps = 1e-9;
};

} // namespace cp