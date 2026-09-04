#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "geom/point.hpp"

namespace cp {

template <class T> bool is_convex_ccw(const std::vector<point<T>>& p) {
  assert(!p.empty());
  for (int i = 0; i < int(p.size()); i++) {
    point<T> p1 = p[(i + 1) % p.size()] - p[i];
    point<T> p2 = p[(i + 2) % p.size()] - p[(i + 1) % p.size()];
    if (internal::less(cross(p1, p2), 0)) return false;
  }
  return true;
}

template <class T> bool is_convex(const std::vector<point<T>>& p) {
  if (is_convex_ccw(p)) return true;
  std::reverse(p.begin(), p.end());
  return is_convex_ccw(p);
}

}  // namespace cp