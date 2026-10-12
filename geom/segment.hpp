#pragma once

#include <algorithm>
#include <iostream>

#include "geom/ccw.hpp"
#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

template <class T> class Segment {
 public:
  Point<T> p, q;
  Segment() {}
  explicit Segment(const Point<T>& _p, const Point<T>& _q) : p(_p), q(_q) {}
  template <class U> explicit Segment(const Segment<U>& s) : p(s.p), q(s.q) {}
  explicit operator Line<T>() const { return Line<T>(p, q); }
};

template <class T> long double arg(const Segment<T>& s) {
  return arg(Line<T>(s));
}

template <class T> bool is_parallel(const Segment<T>& s, const Segment<T>& t) {
  return is_parallel(Line<T>(s), Line<T>(t));
}
template <class T>
bool is_orthogonal(const Segment<T>& s, const Segment<T>& t) {
  return is_orthogonal(Line<T>(s), Line<T>(t));
}

template <class T> bool on(const Point<T>& p, const Segment<T>& s) {
  return ccw(s.p, s.q, p) == 0;
}

template <class T> std::istream& operator>>(std::istream& is, Segment<T>& l) {
  return is >> l.p >> l.q;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const Segment<T>& l) {
  return os << l.p << " " << l.q;
}

}  // namespace cp