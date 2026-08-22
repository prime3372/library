#pragma once

#include <iostream>

#include "geom/point.hpp"

namespace cp {

template <class T> class basic_line {
 public:
  basic_point<T> p, q;
  basic_line() : p(0, 0), q(1, 0) {}
  explicit basic_line(const basic_point<T>& _p, const basic_point<T>& _q)
      : p(_p), q(_q) {}
};

using line = basic_line<long double>;
using iline = basic_line<long long>;

template <class T> long double arg(const basic_line<T>& l) {
  return arg(l.q - l.p);
}

template <class T>
bool is_parallel(const basic_line<T>& l, const basic_line<T>& m) {
  return is_parallel(l.q - l.p, m.q - m.p);
}
template <class T>
bool is_orthogonal(const basic_line<T>& l, const basic_line<T>& m) {
  return is_orthogonal(l.q - l.p, m.q - m.p);
}

template <class T> bool is_on(const basic_point<T>& p, const basic_line<T>& l) {
  return internal::geom_cmp(cross(l.p - p, l.q - p)) == 0;
}

template <class T>
bool is_same(const basic_line<T>& l, const basic_line<T>& m) {
  return is_parallel(l, m) && is_on(m.p, l);
}

template <class T>
std::istream& operator>>(std::istream& is, basic_line<T>& l) {
  return is >> l.p >> l.q;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const basic_line<T>& l) {
  return os << l.p << " " << l.q;
}

}  // namespace cp