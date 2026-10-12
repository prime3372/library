#pragma once

#include <cmath>
#include <iostream>

namespace cp {

namespace internal {

constexpr long double eps = 1e-9;
template <class T> bool equal(T x, T y) { return std::abs(x - y) < eps; }
template <class T> bool less(T x, T y) { return x < y - eps; }
template <class T> bool less_equal(T x, T y) { return x < y + eps; }

}  // namespace internal

template <class T> class Point {
 public:
  T x, y;
  Point() : x(0), y(0) {}
  Point(T _x, T _y) : x(_x), y(_y) {}
  template <class U> explicit Point(const Point<U>& p) : x(p.x), y(p.y) {}

  Point& operator+=(const Point& p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  Point& operator-=(const Point& p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }
  template <class U> Point& operator*=(U s) {
    x *= s;
    y *= s;
    return *this;
  }
  template <class U> Point& operator/=(U s) {
    x /= s;
    y /= s;
    return *this;
  }

  Point operator+() const { return Point(x, y); }
  Point operator-() const { return Point(-x, -y); }
};

template <class T> T norm(const Point<T>& p) { return p.x * p.x + p.y * p.y; }

template <class T> long double abs(const Point<T>& p) {
  return std::sqrt((long double)(p.x) * p.x + (long double)(p.y) * p.y);
}

template <class T> long double arg(const Point<T>& p) {
  return std::atan2((long double)(p.y), (long double)(p.x));
}

template <class T> T dot(const Point<T>& p, const Point<T>& q) {
  return p.x * q.x + p.y * q.y;
}
template <class T> T cross(const Point<T>& p, const Point<T>& q) {
  return p.x * q.y - p.y * q.x;
}

template <class T> bool is_parallel(const Point<T>& p, const Point<T>& q) {
  return internal::equal<T>(cross(p, q), 0);
}
template <class T> bool is_orthogonal(const Point<T>& p, const Point<T>& q) {
  return internal::equal<T>(dot(p, q), 0);
}

template <class T> bool is_same(const Point<T>& p, const Point<T>& q) {
  return internal::equal(p.x, q.x) && internal::equal(p.y, q.y);
}

template <class T> Point<T> operator+(const Point<T>& p, const Point<T>& q) {
  return Point<T>(p) += q;
}
template <class T> Point<T> operator-(const Point<T>& p, const Point<T>& q) {
  return Point<T>(p) -= q;
}
template <class T, class U> Point<T> operator*(const Point<T>& p, U s) {
  return Point<T>(p) *= s;
}
template <class T, class U> Point<T> operator*(U s, const Point<T>& p) {
  return Point<T>(p) *= s;
}
template <class T, class U> Point<T> operator/(const Point<T>& p, U s) {
  return Point<T>(p) /= s;
}

template <class T> bool operator==(const Point<T>& p, const Point<T>& q) {
  return (p.x == q.x) && (p.y == q.y);
}
template <class T> bool operator<(const Point<T>& p, const Point<T>& q) {
  return (p.x < q.x) || (p.x == q.x && p.y < q.y);
}
template <class T> bool operator>(const Point<T>& p, const Point<T>& q) {
  return q < p;
}
template <class T> bool operator<=(const Point<T>& p, const Point<T>& q) {
  return !(p > q);
}
template <class T> bool operator>=(const Point<T>& p, const Point<T>& q) {
  return !(p < q);
}

template <class T> std::istream& operator>>(std::istream& is, Point<T>& p) {
  return is >> p.x >> p.y;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
  return os << p.x << " " << p.y;
}

}  // namespace cp