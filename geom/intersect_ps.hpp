#pragma once

#include "geom/ccw.hpp"
#include "geom/point.hpp"
#include "geom/segment.hpp"

namespace cp {

template <class T> bool intersect(const point<T>& p, const segment<T>& s) {
  return ccw(s.p, s.q, p) == 0;
}

}  // namespace cp
