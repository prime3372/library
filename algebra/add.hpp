#pragma once

#include <type_traits>

#include "../util/type_traits.hpp"

namespace cp {

template <class> struct add {};

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct add<T> {
  using S = T;
  static constexpr S op(S x, S y) { return x + y; }
  static constexpr S e() { return 0; }
  static constexpr S inv(S x) { return -x; }
};

} // namespace cp
