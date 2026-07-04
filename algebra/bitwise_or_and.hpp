#pragma once

#include <concepts>

namespace cp {

template <std::integral T> struct bitwise_or_and {
  using S = T;
  static constexpr S op(S x, S y) { return x | y; }
  static constexpr S e() { return 0; }

  using F = T;
  static constexpr S mapping(F f, S x) { return f | x; }
  static constexpr F composition(F g, F f) { return g & f; }
  static constexpr F id() { return -1; }

  static constexpr S add(S x, S y) { return x | y; }
  static constexpr S mul(S x, S y) { return x & y; }
  static constexpr S zero() { return 0; }
  static constexpr S one() { return -1; }
};

} // namespace cp