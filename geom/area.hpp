#pragma once

#include <cmath>
#include <vector>

#include "geom/point.hpp"

namespace cp {

// @return signed area of polygon p
template <class T> long double area(const std::vector<point<T>>& p) {
  long double ans = 0;
  for (int i = 0; i < int(p.size()); ++i) {
    ans += cross(p[i], p[(i + 1) % p.size()]);
  }
  return ans * 0.5;
}

}  // namespace cp