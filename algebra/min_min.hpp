#pragma once

#include <algorithm>

namespace cp {

namespace alg {

template <class T, T upper> struct min_min {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return upper; }

  using F = T;
  static S mapping(F f, S x) { return std::min(f, x); }
  static F composition(F g, F f) { return std::min(g, f); }
  static F id() { return upper; }
};

} // namespace alg

} // namespace cp