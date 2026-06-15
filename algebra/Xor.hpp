#pragma once

#include <concepts>

template <std::integral T> struct Xor {
  using S = T;
  static S op(S x, S y) { return x ^ y; }
  static S e() { return 0; }
  static S inv(S x) { return x; }
  Xor() = delete;
};
