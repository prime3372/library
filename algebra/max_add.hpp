#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T lower> requires std::is_arithmetic_v<T>
struct max_add {
  using S = T;
  static constexpr S op(S x, S y) { return std::max(x, y); }
  static constexpr S e() { return lower; }

  using F = T;
  static constexpr S mapping(F f, S x) { return f + x; }
  static constexpr F composition(F g, F f) { return g + f; }
  static constexpr F id() { return 0; }

  static constexpr S add(S x, S y) { return std::max(x, y); }
  static constexpr S mul(S x, S y) { return x + y; }
  static constexpr S zero() { return lower; }
  static constexpr S one() { return 0; }
};

} // namespace cp