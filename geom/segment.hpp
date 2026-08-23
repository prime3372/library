#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

#include "geom/ccw.hpp"
#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

template <class T> class segment : public line<T> {
 public:
  using line<T>::p;
  using line<T>::q;
  segment() {}
  segment(const point<T>& _p, const point<T>& _q) : line<T>(_p, _q) {}
  template <class U>
  explicit segment(const segment<U>& l)
      : line<T>(point<T>(l.p), point<T>(l.q)) {}
};

template <class T> bool is_on(const point<T>& p, const segment<T>& l) {
  return ccw(l.p, l.q, p) == 0;
}

template <class T> bool is_same(const segment<T>& l, const segment<T>& m) {
  return (is_same(l.p, m.p) && is_same(l.q, m.q)) ||
         (is_same(l.p, m.q) && is_same(l.q, m.p));
}

}  // namespace cp