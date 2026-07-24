#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T lower> requires (std::is_arithmetic_v<T>)
struct max {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }
};

} // namespace cp