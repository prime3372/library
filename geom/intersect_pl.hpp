#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

template <class T> bool intersect(const point<T>& p, const line<T>& l) {
  return internal::equal(cross(l.p - p, l.q - p), 0);
}

}  // namespace cp