#pragma once

#include <concepts>

namespace cp {

template <std::integral T> struct bitwise_xor {
  using S = T;
  static S op(S x, S y) { return x ^ y; }
  static S e() { return 0; }
  static S inv(S x) { return x; }
};

} // namespace cp