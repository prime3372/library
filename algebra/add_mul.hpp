#pragma once

#include <type_traits>

#include "util/type_traits.hpp"

namespace cp {

template <class> struct add_mul {};

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct add_mul<T> {
  using S = T;
  static constexpr S op(S x, S y) { return x + y; }
  static constexpr S e() { return 0; }
  static constexpr S inv(S x) { return -x; }

  using F = T;
  static constexpr S mapping(F f, S x) { return f * x; }
  static constexpr F composition(F g, F f) { return g * f; }
  static constexpr F id() { return 1; }

  static constexpr S add(S x, S y) { return x + y; }
  static constexpr S mul(S x, S y) { return x * y; }
  static constexpr S zero() { return 0; }
  static constexpr S one() { return 1; }
  static constexpr S minus(S x) { return -x; }
  static constexpr S recip(S x) requires std::is_floating_point_v<T> || is_modint_v<T> { return 1 / x; }
};

} // namespace cp
