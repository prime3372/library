#pragma once

#include <type_traits>
#include "Assign.hpp"
#include "Sum.hpp"
#include "../util/type_traits.hpp"

template <class T, T identity>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct Sum_Assign {
  using S = typename Sum<T>::S;
  static S op(S x, S y) { return Sum<T>::op(x, y); }
  static S e() { return Sum<T>::e(); }

  using F = typename Assign<T>::F;
  static S mapping(F f, S x) { return f.id ? x : f.val; }
  static F composition(F g, F f) { return Assign<T>::composition(g, f); }
  static F id() { return Assign<T>::id(); }

  Sum_Assign() = delete;
};
