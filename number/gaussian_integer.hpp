#pragma once

#include <iostream>
#include <utility>

#include "util/math_utility.hpp"
#include "util/type_traits.hpp"

namespace cp {

class gaussian_integer {
  using gint = gaussian_integer;

 public:
  long long x, y;
  gaussian_integer() : x(0), y(0) {}
  gaussian_integer(long long _x) : x(_x), y(0) {}
  gaussian_integer(long long _x, long long _y) : x(_x), y(_y) {}

  gint conj() const { return gint(x, -y); }
  long long norm() const { return x * x + y * y; }

  gint operator+() const { return *this; }
  gint operator-() const { return gint(-x, -y); }

  gint& operator+=(const gint& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  gint& operator-=(const gint& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  gint& operator*=(const gint& rhs) {
    long long x2 = x * rhs.x - y * rhs.y;
    long long y2 = x * rhs.y + y * rhs.x;
    return *this = gint(x2, y2);
  }
  gint& operator/=(const gint& rhs) {
    long long n = rhs.norm();
    *this *= rhs.conj();
    x = div_floor(x + n / 2, n);
    y = div_floor(y + n / 2, n);
    return *this;
  }
  gint& operator%=(const gint& rhs) {
    *this -= (*this / rhs) * rhs;
    return *this;
  }

  friend gint operator+(const gint& lhs, const gint& rhs) {
    return gint(lhs) += rhs;
  }
  friend gint operator-(const gint& lhs, const gint& rhs) {
    return gint(lhs) -= rhs;
  }
  friend gint operator*(const gint& lhs, const gint& rhs) {
    return gint(lhs) *= rhs;
  }
  friend gint operator/(const gint& lhs, const gint& rhs) {
    return gint(lhs) /= rhs;
  }
  friend gint operator%(const gint& lhs, const gint& rhs) {
    return gint(lhs) %= rhs;
  }

  friend bool operator==(const gint& lhs, const gint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const gint& lhs, const gint& rhs) {
    return !(lhs == rhs);
  }
  friend bool operator<(const gint& lhs, const gint& rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
  }
  friend bool operator>(const gint& lhs, const gint& rhs) {
    return rhs < lhs;
  }
  friend bool operator<=(const gint& lhs, const gint& rhs) {
    return !(lhs > rhs);
  }
  friend bool operator>=(const gint& lhs, const gint& rhs) {
    return !(lhs < rhs);
  }

  friend std::istream& operator>>(std::istream& is, gint& z) {
    return is >> z.x >> z.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const gint& z) {
    return os << z.x << " " << z.y;
  }
};

}  // namespace cp