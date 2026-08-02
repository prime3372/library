#pragma once

#include <algorithm>

namespace cp {

template <class T, T upper> struct min_assign {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return upper; }

  struct F {
    T val;
    bool id;
    F() : val(), id(true) {}
    F(T v) : val(v), id(false) {}
  };
  static S mapping(F f, S x) { return f.id ? x : f.val; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return F(); }
};

} // namespace cp