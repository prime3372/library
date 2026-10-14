#pragma once

#include <iostream>

#include "geom/point.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class T> struct Line {
 public:
  Point<T> p, q;
  Line() : p(0, 0), q(1, 0) {}
  explicit Line(const Point<T>& _p, const Point<T>& _q) : p(_p), q(_q) {}
  template <class U>
  explicit Line(const Line<U>& l) : p(Point<T>(l.p)), q(Point<T>(l.q)) {}
};

template <class T> long double arg(const Line<T>& l) { return arg(l.q - l.p); }

Point<long double> direction(const Line<long double>& l) {
  return (l.q - l.p) / abs(l.q - l.p);
}
template <class T> Point<long double> direction(const Line<T>& l) {
  return direction(Line<long double>(l));
}

template <class T> bool is_parallel(const Line<T>& l, const Line<T>& m) {
  return is_parallel(l.q - l.p, m.q - m.p);
}
template <class T> bool is_orthogonal(const Line<T>& l, const Line<T>& m) {
  return is_orthogonal(l.q - l.p, m.q - m.p);
}

template <class T> bool on(const Point<T>& p, const Line<T>& l) {
  return internal::equal(cross(l.p - p, l.q - p), 0);
}

template <class T> std::istream& operator>>(std::istream& is, Line<T>& l) {
  return is >> l.p >> l.q;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const Line<T>& l) {
  return os << l.p << " " << l.q;
}

}  // namespace cp