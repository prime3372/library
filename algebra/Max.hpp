#pragma once

#include <algorithm>
#include <type_traits>

template <class T, T lower> requires std::is_arithmetic_v<T>
struct Max {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }
  Max() = delete;
};
