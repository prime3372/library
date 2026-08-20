#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>

namespace cp {

template <class T> class basic_point {
 public:
  T x, y;

  basic_point& operator+=(const basic_point& p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  basic_point& operator-=(const basic_point& p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }
  basic_point& operator*=(T s) {
    x *= s;
    y *= s;
    return *this;
  }
  basic_point& operator/=(T s) {
    x /= s;
    y /= s;
    return *this;
  }

  basic_point operator+() const { return basic_point(x, y); }
  basic_point operator-() const { return basic_point(-x, -y); }

  friend basic_point operator+(const basic_point& p, const basic_point& q) {
    return basic_point(p) += q;
  }
  friend basic_point operator-(const basic_point& p, const basic_point& q) {
    return basic_point(p) -= q;
  }
  friend basic_point operator*(const basic_point& p, T q) {
    return basic_point(p) *= q;
  }
  friend basic_point operator*(T p, const basic_point& q) {
    return basic_point(q) *= p;
  }
  friend basic_point operator/(const basic_point& p, T q) {
    return basic_point(p) /= q;
  }

  friend T norm(const basic_point& p) { return p.x * p.x + p.y * p.y; }
  friend double abs(const basic_point& p) {
    return std::sqrt(p.x * p.x + p.y * p.y);
  }

  friend T dot(const basic_point& p, const basic_point& q) {
    return p.x * q.x + p.y * q.y;
  }
  friend T cross(const basic_point& p, const basic_point& q) {
    return p.x * q.y - p.y * q.x;
  }

  friend double arg(const basic_point& p) { return std::atan2(p.y, p.x); }

  friend basic_point rot90(const basic_point& p) {
    return basic_point(p.y, -p.x);
  }
  friend basic_point rot(const basic_point& p, double rad) {
    double theta = arg(p) + rad;
    return norm(p) * basic_point(std::cos(theta), std::sin(theta));
  }

  friend bool is_same(const basic_point& p, const basic_point& q) {
    return equal(p.x, q.x) && equal(p.y, q.y);
  }
  friend bool is_parallel(const basic_point& p, const basic_point& q) {
    return equal(cross(p, q), 0);
  }
  friend bool is_orthogonal(const basic_point& p, const basic_point& q) {
    return equal(dot(p, q), 0);
  }

  friend std::istream& operator>>(std::istream& is, basic_point& p) {
    return is >> p.x >> p.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const basic_point& p) {
    return os << p.x << " " << p.y;
  }

 private:
  friend class line;

  static bool equal(T x, T y) {
    if (std::is_floating_point_v<T>) {
      static constexpr double eps = 1e-9;
      return std::abs(x - y) < eps;
    } else {
      return x == y;
    }
  }
};

using point = basic_point<double>;
using ipoint = basic_point<long long>;

bool operator==(const ipoint& p, const ipoint& q) {
  return p.x == q.x && p.y == q.y;
}
bool operator!=(const ipoint& p, const ipoint& q) { return !(p == q); }
bool operator<(const ipoint& p, const ipoint& q) {
  return p.x < q.x || (p.x == q.x && p.y < q.y);
}
bool operator>(const ipoint& p, const ipoint& q) { return q < p; }
bool operator<=(const ipoint& p, const ipoint& q) { return !(p > q); }
bool operator>=(const ipoint& p, const ipoint& q) { return !(p < q); }

}  // namespace cp