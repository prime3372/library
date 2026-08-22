#pragma once

#include <cmath>
#include <iostream>
#include <type_traits>

namespace cp {

namespace internal {

template <class T> int geom_cmp(T x, T y = 0) {
  constexpr long double eps = 1e-9;
  if (std::is_floating_point_v<T>) {
    return x - y < -eps ? -1 : x - y > eps ? 1 : 0;
  } else {
    return x < y ? -1 : x > y ? 1 : 0;
  }
}

}  // namespace internal

template <class T> class basic_point {
 public:
  T x, y;
  basic_point() : x(0), y(0) {}
  basic_point(T _x, T _y) : x(_x), y(_y) {}

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
  template <class U> basic_point& operator*=(U s) {
    x *= s;
    y *= s;
    return *this;
  }
  template <class U> basic_point& operator/=(U s) {
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
  template <class U> friend basic_point operator*(const basic_point& p, U s) {
    return basic_point(p) *= s;
  }
  template <class U> friend basic_point operator*(U s, const basic_point& p) {
    return basic_point(p) *= s;
  }
  template <class U> friend basic_point operator/(const basic_point& p, U s) {
    return basic_point(p) /= s;
  }
};

using point = basic_point<long double>;
using ipoint = basic_point<long long>;

template <class T> T norm(const basic_point<T>& p) {
  return p.x * p.x + p.y * p.y;
}
template <class T> long double abs(const basic_point<T>& p) {
  return std::sqrt(norm(p));
}

template <class T> T dot(const basic_point<T>& p, const basic_point<T>& q) {
  return p.x * q.x + p.y * q.y;
}
template <class T> T cross(const basic_point<T>& p, const basic_point<T>& q) {
  return p.x * q.y - p.y * q.x;
}

template <class T> long double arg(const basic_point<T>& p) {
  return std::atan2(p.y, p.x);
}

template <class T> basic_point<T> rot90(const basic_point<T>& p) {
  return basic_point<T>(p.y, -p.x);
}

template <class T>
bool is_same(const basic_point<T>& p, const basic_point<T>& q) {
  return internal::geom_cmp(p.x, q.x) == 0 && internal::geom_cmp(p.y, q.y) == 0;
}
template <class T>
bool is_parallel(const basic_point<T>& p, const basic_point<T>& q) {
  return internal::geom_cmp(cross(p, q)) == 0;
}
template <class T>
bool is_orthogonal(const basic_point<T>& p, const basic_point<T>& q) {
  return internal::geom_cmp(dot(p, q)) == 0;
}

template <class T>
std::istream& operator>>(std::istream& is, basic_point<T>& p) {
  return is >> p.x >> p.y;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const basic_point<T>& p) {
  return os << p.x << " " << p.y;
}

}  // namespace cp