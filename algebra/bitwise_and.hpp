#pragma once

#include <concepts>

namespace cp {

template <std::integral T> struct bitwise_and {
  using S = T;
  static S op(S x, S y) { return x & y; }
  static S e() { return -1; }
};

} // namespace cp