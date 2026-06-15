#pragma once

#include <type_traits>
#include "Assign.hpp"
#include "Sum.hpp"
#include "../util/type_traits.hpp"

template <class T, T infty>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct Sum_Assign {
  using S = typename Sum<T>::S;
  static S op(S x, S y) { return Sum<T>::op(x, y); }
  static S e() { return Sum<T>::e(); }

  using F = typename Assign<T>::S;
  static S mapping(F f, S x) { return f.id ? x : {f.val * x.len, x.len}; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return Assign<T>::e(); }

  Sum_Assign() = delete;
};
