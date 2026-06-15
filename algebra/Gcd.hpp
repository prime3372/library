#pragma once

#include <concepts>
#include <numeric>

template <std::integral T> struct Gcd {
  using S = T;
  static S op(S x, S y) { return std::gcd(x, y); }
  static S e() { return 0; }
  Gcd() = delete;
};
