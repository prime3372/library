#pragma once

#include <algorithm>
#include <type_traits>

template <class T, T up> requires std::is_arithmetic_v<T>
struct Min {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return up; }
  Min() = delete;
};
