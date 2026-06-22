#pragma once

#include <algorithm>
#include <type_traits>

template <class T, T lower> requires std::is_arithmetic_v<T>
struct Max_Max {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }

  using F = T;
  static S mapping(F f, S x) { return std::max(f, x); }
  static F composition(F g, F f) { return std::max(g, f); }
  static F id() { return lower; }

  Max_Max() = delete;
};
