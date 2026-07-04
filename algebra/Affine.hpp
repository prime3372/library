#pragma once

#include <type_traits>

#include "../util/type_traits.hpp"

namespace cp {

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct affine {
  struct S {
    T a, b;
    S() : a(1), b(0) {}
    S(T _a, T _b) : a(_a), b(_b) {}
  };
  static constexpr S op(S f, S g) { return {g.a * f.a, g.a * f.b + g.b}; }
  static constexpr S e() { return S(); }
  static constexpr S inv(S f) requires std::is_floating_point_v<T> || is_modint_v<T> { return {1 / f.a, -f.b / f.a}; }
};

} // namespace cp