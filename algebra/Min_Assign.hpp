#pragma once

#include <algorithm>
#include <type_traits>
#include "Assign.hpp"

template <class T, T infty>
  requires std::is_arithmetic_v<T>
struct Min_Assign {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return infty; }

  using F = typename Assign<T>::S;
  static S mapping(F f, S x) { return f.id ? x : f.val; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return Assign<T>::e(); }

  Min_Assign() = delete;
};
