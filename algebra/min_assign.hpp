#pragma once

#include <algorithm>

namespace cp {

namespace alg {

template <class T, T upper> struct min_assign {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return upper; }

  struct F {
    T val;
    bool id;
  };
  static S mapping(F f, S x) { return f.id ? x : f.val; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return F{upper, true}; }
};

} // namespace alg

} // namespace cp