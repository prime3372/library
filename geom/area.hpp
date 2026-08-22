#pragma once

#include <cmath>
#include <vector>

#include "geom/point.hpp"

namespace cp {

template <class T> long double area(const std::vector<basic_point<T>>& ps) {
  T ans = 0;
  for (int i = 0; i < int(ps.size()); ++i) {
    ans += cross(ps[i], ps[(i + 1) % ps.size()]);
  }
  return std::abs((long double)(ans) * 0.5);
}

}  // namespace cp