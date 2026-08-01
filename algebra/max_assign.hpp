#pragma once

#include <algorithm>

namespace cp {

template <class T, T lower> struct max_assign {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }

  struct F {
    T val;
    bool id;
    F() : val(), id(true) {}
    F(T v) : val(v), id(false) {}
  }
  static S mapping(F f, S x) { return f.id ? x : f; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return F(); }
};

} // namespace cp