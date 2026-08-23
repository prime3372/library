#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

#include "geom/ccw.hpp"
#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

template <class T> class basic_segment : public basic_line<T> {
 public:
  using basic_line<T>::p;
  using basic_line<T>::q;
  basic_segment() {}
  basic_segment(const basic_point<T>& _p, const basic_point<T>& _q)
      : basic_line<T>(_p, _q) {}

  explicit operator basic_line<T>() { return basic_line<T>(p, q); }
};

using segment = basic_segment<long double>;
using isegment = basic_segment<long long>;

template <class T>
bool is_on(const basic_point<T>& p, const basic_segment<T>& l) {
  return ccw(l.p, l.q, p) == 0;
}

template <class T>
bool is_same(const basic_segment<T>& l, const basic_segment<T>& m) {
  return (is_same(l.p, m.p) && is_same(l.q, m.q)) ||
         (is_same(l.p, m.q) && is_same(l.q, m.p));
}

}  // namespace cp