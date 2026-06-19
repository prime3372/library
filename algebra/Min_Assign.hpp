#pragma once

#include <algorithm>
#include <type_traits>
#include "Assign.hpp"

template <class T, T upper> requires std::is_arithmetic_v<T>
struct Min_Assign {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return upper; }

  using F = typename Assign<T>::F;
  static S mapping(F f, S x) { return f.id ? x : f.val; }
  static F composition(F g, F f) { return Assign<T>::composition(g, f); }
  static F id() { return Assign<T>::id(); }

  Min_Assign() = delete;
};
