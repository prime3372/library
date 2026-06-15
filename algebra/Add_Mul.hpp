#pragma once

#include <type_traits>
#include "../util/type_traits.hpp"

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct Add_Mul {
  using S = T;
  static S op(S x, S y) { return x + y; }
  static S e() { return 0; }
  static S inv(S x) { return -x; }

  using F = T;
  static S mapping(F f, S x) { return f * x; }
  static F composition(F g, F f) { return g * f; }
  static F id() { return 1; }

  static S add(S x, S y) { return x + y; }
  static S mul(S x, S y) { return x * y; }
  static S zero() { return 0; }
  static S one() { return 1; }
  static S minus(S x) { return -x; }
  static S recip(S x) requires std::is_floating_point_v<T> || is_modint_v<T> { return 1 / x; }

  Add_Mul() = delete;
};
