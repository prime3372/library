#pragma once

#include <algorithm>
#include <type_traits>
#include "Assign.hpp"

template <class T, T lower> requires std::is_arithmetic_v<T>
struct Max_Assign {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }

  using F = typename Assign<T>::F;
  static S mapping(F f, S x) { return f.id ? x : f.val; }
  static F composition(F g, F f) { return Assign<T>::composition(g, f); }
  static F id() { return Assign<T>::id(); }
  
  Max_Assign() = delete;
};
