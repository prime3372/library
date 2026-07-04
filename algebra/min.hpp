#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T upper> requires std::is_arithmetic_v<T>
struct min {
  using S = T;
  static constexpr S op(S x, S y) { return std::min(x, y); }
  static constexpr S e() { return upper; }
};

} // namespace cp