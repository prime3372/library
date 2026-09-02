#pragma once

#include <algorithm>
#include <vector>

#include "geom/point.hpp"

namespace cp {

template <bool include_boundary = false, class T>
std::vector<point<T>> convex_hull(std::vector<point<T>> p) {
  std::sort(p.begin(), p.end());
  p.erase(std::unique(p.begin(), p.end()), p.end());
  int n = int(p.size());
  if (n <= 2) return p;

  std::vector<point<T>> ch;
  auto check_convex = [&](const point<T>& q) {
    const point<T>& p1 = ch[ch.size() - 1];
    const point<T>& p0 = ch[ch.size() - 2];
    return include_boundary ? internal::less_equal<T>(0, cross(p1 - p0, q - p1))
                            : internal::less<T>(0, cross(p1 - p0, q - p1));
  };

  // lower convex hull
  for (int i = 0; i < n; i++) {
    while (ch.size() >= 2 && !check_convex(p[i])) ch.pop_back();
    ch.push_back(p[i]);
  }

  // upper convex hull
  int t = int(ch.size()) + 1;
  for (int i = n - 2; i >= 0; i--) {
    while (int(ch.size()) >= t && !check_convex(p[i])) ch.pop_back();
    ch.push_back(p[i]);
  }
  ch.pop_back();

  return ch;
}

}  // namespace cp