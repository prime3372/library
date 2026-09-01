#pragma once

#include "geom/ccw.hpp"
#include "geom/line.hpp"
#include "geom/segment.hpp"

namespace cp {

template <class T> bool intersect(const line<T>& l, const segment<T>& s) {
  return ccw(l.p, l.q, s.p) * ccw(l.p, l.q, s.q) != 1;
}

}  // namespace cp