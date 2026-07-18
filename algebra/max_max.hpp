#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T lower> requires (std::is_arithmetic_v<T>)
struct max_max {
  using S = T;
  static constexpr S op(S x, S y) { return std::max(x, y); }
  static constexpr S e() { return lower; }

  using F = T;
  static constexpr S mapping(F f, S x) { return std::max(f, x); }
  static constexpr F composition(F g, F f) { return std::max(g, f); }
  static constexpr F id() { return lower; }
};

} // namespace cp