#pragma once

#include <type_traits>
#include "Affine.hpp"
#include "Sum.hpp"
#include "../util/type_traits.hpp"

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct Sum_Affine {
  using S = typename Sum<T>::S;
  static S op(S x, S y) { return Sum<T>::op(x, y); }
  static S e() { return Sum<T>::e(); }

  using F = typename Affine<T>::S;
  static S mapping(F f, S x) { return S{f.a * x.val + f.b * x.len, x.len}; }
  static F composition(F g, F f) { return Affine<T>::op(f, g); }
  static F id() { return Affine<T>::e(); }

  Sum_Affine() = delete;
};
