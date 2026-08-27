#pragma once

#include <cstddef>
#include <iostream>

namespace cp {

namespace alg {

template <class T> struct arithmetic_add {
  struct S {
    T val_sum;
    size_t index_sum, len;
  };
  static S op(S x, S y) {
    return S{x.val_sum + y.val_sum, x.index_sum + y.index_sum, x.len + y.len};
  }
  static S e() { return S{0, 0, 0}; }

  struct F {
    T a, b;
  };
  static S mapping(F f, S x) {
    return S{x.val_sum + f.a * x.index_sum + f.b * x.len, x.index_sum, x.len};
  }
  static F composition(F g, F f) { return F{f.a + g.a, f.b + g.b}; }
  static F id() { return F{0, 0}; }
};

}  // namespace alg

}  // namespace cp