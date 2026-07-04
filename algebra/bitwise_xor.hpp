#pragma once

#include <concepts>

namespace cp {

template <std::integral T> struct bitwise_xor {
  using S = T;
  static constexpr S op(S x, S y) { return x ^ y; }
  static constexpr S e() { return 0; }
  static constexpr S inv(S x) { return x; }
};

} // namespace cp