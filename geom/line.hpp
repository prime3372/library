#pragma once

#include <iostream>

#include "geom/point.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> class line {
 public:
  point<T> p, q;
  line() : p(0, 0), q(1, 0) {}
  line(const point<T>& _p, const point<T>& _q) : p(_p), q(_q) {}
  template <class U>
  explicit line(const line<U>& l) : p(point<T>(l.p)), q(point<T>(l.q)) {}
};

template <class T> long double arg(const line<T>& l) { return arg(m.q - m.p); }
template <class T> requires internal::is_integral_v<T>
long double arg(const line<T>& l) {
  return arg(line<long double>(l));
}

template <class T> bool is_parallel(const line<T>& l, const line<T>& m) {
  return is_parallel(l.q - l.p, m.q - m.p);
}
template <class T> bool is_orthogonal(const line<T>& l, const line<T>& m) {
  return is_orthogonal(l.q - l.p, m.q - m.p);
}

template <class T> bool is_on(const point<T>& p, const line<T>& l) {
  return internal::equal(cross(l.p - p, l.q - p), 0);
}

template <class T> bool is_same(const line<T>& l, const line<T>& m) {
  return is_parallel(l, m) && is_on(m.p, l);
}

template <class T> std::istream& operator>>(std::istream& is, line<T>& l) {
  return is >> l.p >> l.q;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const line<T>& l) {
  return os << l.p << " " << l.q;
}

}  // namespace cp