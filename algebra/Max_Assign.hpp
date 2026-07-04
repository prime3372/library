#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T lower, T identity> requires std::is_arithmetic_v<T>
struct max_assign {
  using S = T;
  static constexpr S op(S x, S y) { return std::max(x, y); }
  static constexpr S e() { return lower; }

  using F = typename Assign<T>::F;
  static constexpr S mapping(F f, S x) { return f == identity ? x : f; }
  static constexpr F composition(F g, F f) { return g == identity ? f : g; }
  static constexpr F id() { return identity; }
};

} // namespace cp