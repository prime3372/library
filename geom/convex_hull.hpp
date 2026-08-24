#pragma once

#include <algorithm>
#include <vector>

#include "geom/point.hpp"

namespace cp {

template <bool include_boundary = false, class T>
std::vector<point<T>> convex_hull(std::vector<point<T>> p) {
  constexpr long double th = include_boundary ? -internal::eps : internal::eps;
  std::sort(p.begin(), p.end());
  p.erase(std::unique(p.begin(), p.end()), p.end());
  int n = int(p.size());
  if (n <= 2) return p;
  std::vector<point<T>> ch(2 * n);
  int k = 0;
  for (int i = 0; i < n; i++) {
    while (k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < th) {
      k--;
    }
    ch[k++] = p[i];
  }
  int tmp = k + 1;
  for (int i = n - 2; i >= 0; i--) {
    while (k >= tmp && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 2]) < th) {
      k--;
    }
    ch[k++] = p[i];
  }
  ch.resize(k - 1);
  return ch;
}

}  // namespace cp