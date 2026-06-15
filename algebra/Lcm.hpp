#pragma once

#include <concepts>
#include <numeric>

template <std::integral T> struct Lcm {
  using S = T;
  static S op(S x, S y) { return std::lcm(x, y); }
  static S e() { return 1; }
  Lcm() = delete;
};
