#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T lower> requires (std::is_arithmetic_v<T>)
struct max_add {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }

  using F = T;
  static S mapping(F f, S x) { return f + x; }
  static F composition(F g, F f) { return g + f; }
  static F id() { return 0; }

  static S add(S x, S y) { return std::max(x, y); }
  static S mul(S x, S y) { return x + y; }
  static S zero() { return lower; }
  static S one() { return 0; }
};

} // namespace cp