#pragma once

#include <cstddef>
#include <iostream>

namespace cp {

namespace alg {

template <class T> struct sum_assign {
  struct S {
    T val;
    size_t len;

    // for debugging
    friend std::ostream& operator<<(std::ostream& os, const S& x) {
      os << x.val;
      return os;
    }
  };
  static S op(S x, S y) { return S{x.val + y.val, x.len + y.len}; }
  static S e() { return S(); }

  struct F {
    T val;
    bool id;
  };
  static S mapping(F f, S x) { return f.id ? x : S{f.val * x.len, x.len}; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return F(); }
};

} // namespace alg

} // namespace cp