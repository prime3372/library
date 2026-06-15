#pragma once

#include <algorithm>
#include <type_traits>

template <class T, T infty> requires is_arithmetic_v<T>
struct Max_Add {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return -infty; }
  using F = T;
  static S mapping(F f, S x) { return f + x; }
  static F composition(F g, F f) { return g + f; }
  static F id() { return 0; }

  static S add(S x, S y) { return std::max(x, y); }
  static S mul(S x, S y) { return x + y; }
  static S zero() { return -infty; }
  static S one() { return 0; }

  Max_Add() = delete;
};
