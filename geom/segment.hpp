#pragma once

#include <algorithm>
#include <iostream>

#include "geom/ccw.hpp"
#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

template <class T> class segment {
 public:
  point<T> p, q;
  segment() {}
  explicit segment(const point<T>& _p, const point<T>& _q) : p(_p), q(_q) {}
  template <class U> explicit segment(const segment<U>& s) : p(s.p), q(s.q) {}
  explicit operator line<T>() const { return line<T>(p, q); }
};

template <class T> long double arg(const segment<T>& s) {
  return arg(line<T>(s));
}

template <class T> bool is_parallel(const segment<T>& s, const segment<T>& t) {
  return is_parallel(line<T>(s), line<T>(t));
}
template <class T>
bool is_orthogonal(const segment<T>& s, const segment<T>& t) {
  return is_orthogonal(line<T>(s), line<T>(t));
}

template <class T> bool on(const point<T>& p, const segment<T>& s) {
  return ccw(s.p, s.q, p) == 0;
}

template <class T> std::istream& operator>>(std::istream& is, segment<T>& l) {
  return is >> l.p >> l.q;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const segment<T>& l) {
  return os << l.p << " " << l.q;
}

}  // namespace cp