#pragma once

#include "geom/ccw.hpp"
#include "geom/line.hpp"
#include "geom/segment.hpp"

namespace cp {

template <class T> bool intersect(const line<T>& l, const line<T>& m) {
  return !is_parallel(l, m) || on(l.p, m);
}

template <class T> bool intersect(const line<T>& l, const segment<T>& s) {
  return ccw(l.p, l.q, s.p) * ccw(l.p, l.q, s.q) != 1;
}

template <class T> bool intersect(const segment<T>& s, const segment<T>& t) {
  int a = ccw(s.p, s.q, t.p) * ccw(s.p, s.q, t.q);
  int b = ccw(t.p, t.q, s.p) * ccw(t.p, t.q, s.q);
  return a == 0 || b == 0 || (a == -1 && b == -1);
}

}  // namespace cp