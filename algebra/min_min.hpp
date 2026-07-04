#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T upper> requires std::is_arithmetic_v<T>
struct min_min {
  using S = T;
  static constexpr S op(S x, S y) { return std::min(x, y); }
  static constexpr S e() { return upper; }

  using F = T;
  static constexpr S mapping(F f, S x) { return std::min(f, x); }
  static constexpr F composition(F g, F f) { return std::min(g, f); }
  static constexpr F id() { return upper; }
};

} // namespace cp