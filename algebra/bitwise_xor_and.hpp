#pragma once

#include <concepts>

namespace cp {

template <std::integral T> struct bitwise_xor_and {
  using S = T;
  static S op(S x, S y) { return x ^ y; }
  static S e() { return 0; }

  using F = T;
  static S mapping(F f, S x) { return f ^ x; }
  static F composition(F g, F f) { return g & f; }
  static F id() { return -1; }

  static S add(S x, S y) { return x ^ y; }
  static S mul(S x, S y) { return x & y; }
  static S zero() { return 0; }
  static S one() { return -1; }
  static S minus(S x) { return x; }
};

} // namespace cp