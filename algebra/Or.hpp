#pragma once

#include <concepts>

template <std::integral T> struct Or {
  using S = T;
  static S op(S x, S y) { return x | y; }
  static S e() { return 0; }
  Or() = delete;
};
