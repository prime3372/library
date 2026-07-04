#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T upper> requires std::is_arithmetic_v<T>
struct min_add {
  using S = T;
  static constexpr S op(S x, S y) { return std::min(x, y); }
  static constexpr S e() { return upper; }

  using F = T;
  static constexpr S mapping(F f, S x) { return f + x; }
  static constexpr F composition(F g, F f) { return g + f; }
  static constexpr F id() { return 0; }

  static constexpr S add(S x, S y) { return std::min(x, y); }
  static constexpr S mul(S x, S y) { return x + y; }
  static constexpr S zero() { return upper; }
  static constexpr S one() { return 0; }
};

} // namespace cp