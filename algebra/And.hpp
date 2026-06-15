#pragma once

#include <concepts>
s
template <std::integral T> struct And {
  using S = T;
  static S op(S x, S y) { return x & y; }
  static S e() { return -1; }
  And() = delete;
};
