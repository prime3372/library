#pragma once

#include <algorithm>
#include <type_traits>

template <class T, T upper> requires std::is_arithmetic_v<T>
struct Min_Min {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return upper; }

  using F = T;
  static S mapping(F f, S x) { return std::min(f, x); }
  static F composition(F g, F f) { return std::min(g, f); }
  static F id() { return upper; }

  Min_Min() = delete;
};
