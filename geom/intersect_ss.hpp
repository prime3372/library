#pragma once

#include "geom/ccw.hpp"
#include "geom/segment.hpp"

namespace cp {

template <class T> bool intersect(const segment<T>& s, const segment<T>& t) {
  int a = ccw(s.p, s.q, t.p) * ccw(s.p, s.q, t.q);
  int b = ccw(t.p, t.q, s.p) * ccw(t.p, t.q, s.q);
  return a == 0 || b == 0 || (a == -1 && b == -1);
}

}  // namespace cp