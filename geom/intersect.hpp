#pragma once

#include "geom/ccw.hpp"
#include "geom/line.hpp"
#include "geom/segment.hpp"

namespace cp {

template <class T> bool intersect(const line<T>& l, const line<T>& m) {
  return !is_parallel(l, m) || is_on(l.p, m);
}

template <class T> bool intersect(const line<T>& l, const segment<T>& m) {
  return ccw(l.p, l.q, m.p) * ccw(l.p, l.q, m.q) != 1;
}
template <class T> bool intersect(const segment<T>& l, const line<T>& m) {
  return intersect(m, l);
}

template <class T> bool intersect(const segment<T>& l, const segment<T>& m) {
  int a = ccw(l.p, l.q, m.p) * ccw(l.p, l.q, m.q);
  int b = ccw(m.p, m.q, l.p) * ccw(m.p, m.q, l.q);
  return a == 0 || b == 0 || (a == -1 && b == -1);
}

}  // namespace cp