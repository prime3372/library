#pragma once

#include <type_traits>

#include "util/type_traits.hpp"

namespace cp {

template <class T>
  requires (std::is_arithmetic_v<T> || is_modint_v<T>)
struct add {
  using S = T;
  static S op(S x, S y) { return x + y; }
  static S e() { return 0; }
  static S inv(S x) { return -x; }
};

} // namespace cp