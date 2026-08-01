#pragma once

#include <algorithm>

namespace cp {

template <class T, T lower> struct max_max {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }

  using F = T;
  static S mapping(F f, S x) { return std::max(f, x); }
  static F composition(F g, F f) { return std::max(g, f); }
  static F id() { return lower; }
};

} // namespace cp