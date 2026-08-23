#pragma once

#include "geom/point.hpp"

namespace cp {

// +1: p0-p1,p0-p2 : counter-clockwise
// -1: p0-p1,p0-p2 : clockwise
// +2: p2-p0-p1
// -2: p0-p1-p2
//  0: p0-p2-p1
template <class T>
int ccw(const point<T>& p0, const point<T>& p1, const point<T>& p2) {
  auto c = cross(p1 - p0, p2 - p0);
  if (internal::less(0, c)) {
    return 1;
  } else if (internal::less(c, 0)) {
    return -1;
  } else if (internal::less(dot(p1 - p0, p2 - p0), 0)) {
    return 2;
  } else if (internal::less(dot(p1 - p0, p1 - p2), 0)) {
    return -2;
  } else {
    return 0;
  }
}

}  // namespace cp