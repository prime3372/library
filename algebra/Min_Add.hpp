#pragma once

#include <algorithm>
#include <type_traits>

template <class T, T up> requires std::is_arithmetic_v<T>
struct Min_Add {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return up; }

  using F = T;
  static S mapping(F f, S x) { return f + x; }
  static F composition(F g, F f) { return g + f; }
  static F id() { return 0; }

  static S add(S x, S y) { return std::min(x, y); }
  static S mul(S x, S y) { return x + y; }
  static S zero() { return up; }
  static S one() { return 0; }

  Min_Add() = delete;
};
