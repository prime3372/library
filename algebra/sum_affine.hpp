#pragma once

#include <cstddef>
#include <type_traits>

#include "algebra/affine.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T>
  requires (std::is_arithmetic_v<T> || is_modint_v<T>)
struct sum_affine {
  struct S {
    T val;
    size_t len;
    S() : val(0), len(0) {}
    S(T v, size_t l) : val(v), len(l) {}
  };
  static S op(S x, S y) { return S{x.val + y.val, x.len + y.len}; }
  static S e() { return S(); }

  using F = typename affine<T>::S;
  static S mapping(F f, S x) { return S{f.a * x.val + f.b * x.len, x.len}; }
  static F composition(F g, F f) { return affine<T>::op(f, g); }
  static F id() { return affine<T>::e(); }
};

} // namespace cp