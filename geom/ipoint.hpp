#pragma once

#include <cassert>
#include <iostream>

namespace cp {

class ipoint {
 public:
  long long x, y;
  ipoint() : x(0), y(0) {}
  ipoint(long long _x, long long _y) : x(_x), y(_y) {}

  ipoint operator+() const { return *this; }
  ipoint operator-() const { return ipoint(-x, -y); }

  ipoint& operator+=(const ipoint& v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  ipoint& operator-=(const ipoint& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  ipoint& operator*=(long long s) {
    x *= s;
    y *= s;
    return *this;
  }
  ipoint& operator/=(long long s) {
    x /= s;
    y /= s;
    return *this;
  }

  friend ipoint operator+(const ipoint& lhs, const ipoint& rhs) {
    return ipoint(lhs) += rhs;
  }
  friend ipoint operator-(const ipoint& lhs, const ipoint& rhs) {
    return ipoint(lhs) -= rhs;
  }
  friend ipoint operator*(const ipoint& lhs, long long rhs) {
    return ipoint(lhs) *= rhs;
  }
  friend ipoint operator*(long long lhs, const ipoint& rhs) {
    return ipoint(rhs) *= lhs;
  }
  friend ipoint operator/(const ipoint& lhs, long long rhs) {
    return ipoint(lhs) /= rhs;
  }
  friend ipoint operator/(long long lhs, const ipoint& rhs) {
    return ipoint(rhs) /= lhs;
  }

  long long dot(const ipoint& rhs) const { return x * rhs.x + y * rhs.y; }
  long long cross(const ipoint& rhs) const { return x * rhs.y - y * rhs.x; }

  long long norm2() const { return x * x + y * y; }

  ipoint rot(long long n = 1) const {
    n = n < 0 ? n % 4 + 4 : n % 4;
    if (n == 0) return {x, y};
    if (n == 1) return {y, -x};
    if (n == 2) return {-x, -y};
    return {-y, x};
  }

  bool is_parallel(const ipoint& rhs) const { return dot(rhs) == 0; }
  bool is_orthogonal(const ipoint& rhs) const { return cross(rhs) == 0; }

  int ort() const {
    if (x == 0 && y == 0) return 0;
    if (x > 0 && y >= 0) return 1;
    if (x <= 0 && y > 0) return 2;
    if (x < 0 && y <= 0) return 3;
    return 4;
  }
  bool argless(const ipoint& other) const {
    int ort1 = ort(), ort2 = other.ort();
    if (ort1 != ort2) return ort1 < ort2;
    return cross(other) > 0;
  }

  friend bool operator==(const ipoint& lhs, const ipoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const ipoint& lhs, const ipoint& rhs) {
    return !(lhs == rhs);
  }

  friend std::istream& operator>>(std::istream& is, ipoint& v) {
    return is >> v.x >> v.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const ipoint& v) {
    return os << v.x << " " << v.y;
  }
};

}  // namespace cp