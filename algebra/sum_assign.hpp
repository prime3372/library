#pragma once

#include <cstddef>
#include <type_traits>

#include "util/type_traits.hpp"

namespace cp {

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct sum_assign {
  struct S {
    T val;
    size_t len;
    S() : val(0), len(0) {}
    S(T v) : val(v), len(1) {}
    S(T v, size_t l) : val(v), len(l) {}
  };
  static constexpr S op(S x, S y) { return S{x.val + y.val, x.len + y.len}; }
  static constexpr S e() { return S(); }

  struct F {
    T val;
    bool id;
    F() : val(), id(true) {}
    F(T v) : val(v), id(false) {}
  };
  static constexpr S mapping(F f, S x) { return f.id ? x : S{f.val * x.len, x.len}; }
  static constexpr F composition(F g, F f) { return g.id ? f : g; }
  static constexpr F id() { return F(); }
};

} // namespace cp