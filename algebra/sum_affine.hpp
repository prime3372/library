#pragma once

#include <cstddef>
#include <iostream>

#include "algebra/affine.hpp"

namespace cp {

namespace alg {

template <class T> struct sum_affine {
  struct S {
    T val;
    size_t len;

    friend std::ostream& operator<<(std::ostream& os, const S& x) {
      os << x.val;
      return os;
    }
  };
  static S op(S x, S y) { return S{x.val + y.val, x.len + y.len}; }
  static S e() { return S{0, 0}; }

  using F = typename affine<T>::S;
  static S mapping(F f, S x) { return S{f.a * x.val + f.b * T(x.len), x.len}; }
  static F composition(F g, F f) { return affine<T>::op(f, g); }
  static F id() { return affine<T>::e(); }
};

}  // namespace alg

}  // namespace cp