#pragma once

#include <concepts>

namespace cp {

template <std::integral T> struct bitwise_or {
  using S = T;
  static constexpr S op(S x, S y) { return x | y; }
  static constexpr S e() { return 0; }
};

} // namespace cp