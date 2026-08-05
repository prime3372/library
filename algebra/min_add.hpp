#pragma once

#include <algorithm>

namespace cp {

template <class T, T upper> struct min_add {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return upper; }

  using F = T;
  static S mapping(F f, S x) { return f + x; }
  static F composition(F g, F f) { return g + f; }
  static F id() { return 0; }
};

} // namespace cp