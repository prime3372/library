#pragma once

#include <algorithm>

namespace cp {

namespace alg {

template <class T, T lower> struct max_add {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }

  using F = T;
  static S mapping(F f, S x) { return f + x; }
  static F composition(F g, F f) { return g + f; }
  static F id() { return 0; }
};

} // namespace alg

} // namespace cp