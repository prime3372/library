#pragma once

#include <cmath>
#include <iostream>

#include "util/type_traits.hpp"

namespace cp {

namespace internal {

constexpr long double eps = 1e-9;
template <class T> bool equal(T x, T y) { return std::abs(x - y) < eps; }
template <class T> bool less(T x, T y) { return x < y - eps; }

}  // namespace internal

template <class T> class point {
 public:
  T x, y;
  point() : x(0), y(0) {}
  point(T _x, T _y) : x(_x), y(_y) {}
  template <class U> explicit point(const point<U>& p) : x(T(p.x)), y(T(p.y)) {}

  point& operator+=(const point& p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  point& operator-=(const point& p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }
  template <class U> point& operator*=(U s) {
    x *= s;
    y *= s;
    return *this;
  }
  template <class U> point& operator/=(U s) {
    x /= s;
    y /= s;
    return *this;
  }

  point operator+() const { return point(x, y); }
  point operator-() const { return point(-x, -y); }
};

template <class T> T norm(const point<T>& p) { return p.x * p.x + p.y * p.y; }

template <class T> long double abs(const point<T>& p) {
  return std::sqrt((long double)(p.x) * p.x + (long double)(p.y) * p.y);
}

template <class T> long double arg(const point<T>& p) {
  return std::atan2((long double)(p.y), (long double)(p.x));
}

template <class T> T dot(const point<T>& p, const point<T>& q) {
  return p.x * q.x + p.y * q.y;
}
template <class T> T cross(const point<T>& p, const point<T>& q) {
  return p.x * q.y - p.y * q.x;
}

template <class T> bool is_parallel(const point<T>& p, const point<T>& q) {
  return internal::equal<T>(cross(p, q), 0);
}
template <class T> bool is_orthogonal(const point<T>& p, const point<T>& q) {
  return internal::equal<T>(dot(p, q), 0);
}

template <class T> bool is_same(const point<T>& p, const point<T>& q) {
  return internal::equal(p.x, q.x) && internal::equal(p.y, q.y);
}

template <class T> point<T> operator+(const point<T>& p, const point<T>& q) {
  return point<T>(p) += q;
}
template <class T> point<T> operator-(const point<T>& p, const point<T>& q) {
  return point<T>(p) -= q;
}
template <class T, class U> point<T> operator*(const point<T>& p, U s) {
  return point<T>(p) *= s;
}
template <class T, class U> point<T> operator*(U s, const point<T>& p) {
  return point<T>(p) *= s;
}
template <class T, class U> point<T> operator/(const point<T>& p, U s) {
  return point<T>(p) /= s;
}

template <class T> bool operator==(const point<T>& p, const point<T>& q) {
  return (p.x == q.x) && (p.y == q.y);
}
template <class T> bool operator<(const point<T>& p, const point<T>& q) {
  return (p.x < q.x) || (p.x == q.x && p.y < q.y);
}
template <class T> bool operator>(const point<T>& p, const point<T>& q) {
  return q < p;
}
template <class T> bool operator<=(const point<T>& p, const point<T>& q) {
  return !(p > q);
}
template <class T> bool operator>=(const point<T>& p, const point<T>& q) {
  return !(p < q);
}

template <class T> std::istream& operator>>(std::istream& is, point<T>& p) {
  return is >> p.x >> p.y;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const point<T>& p) {
  return os << p.x << " " << p.y;
}

}  // namespace cp