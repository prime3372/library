#pragma once

#include <cstddef>
#include <iostream>

#include "algebra/affine.hpp"
#include "util/io_utility.hpp"

namespace cp {

template <class T> struct sum_affine {
  struct S {
    T val;
    size_t len;
    S() : val(0), len(0) {}
    S(T v) : val(v), len(1) {}
    S(T v, size_t l) : val(v), len(l) {}

    // for debugging
    friend std::ostream& operator<<(std::ostream& os, const S& x) {
      os << x.val;
      return os;
    }
  };
  static S op(S x, S y) { return S{x.val + y.val, x.len + y.len}; }
  static S e() { return S(); }

  using F = typename affine<T>::S;
  static S mapping(F f, S x) { return S{f.a * x.val + f.b * x.len, x.len}; }
  static F composition(F g, F f) { return affine<T>::op(f, g); }
  static F id() { return affine<T>::e(); }
};

namespace internal {

template <class T> struct delimiter<typename sum_affine<T>::S> {
  static constexpr char value[] = " ";
};

} // namespace internal

} // namespace cp