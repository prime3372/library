#pragma once

#include <cstddef>
#include "monoid.hpp"

namespace cp {

template <monoid M> struct assign {
  using T = typename M::S;

  struct S {
    T val;
    size_t len;
    S() : val(M::e()), len(0) {}
    S(T v, size_t l) : val(v), len(l) {}
  };
  static constexpr S op(S x, S y) { return S{M::op(x.val, y.val), x.len + y.len}; }
  static constexpr S e() { return S(); }

  struct F {
    T val;
    bool id;
    F() : val(), id(true) {}
    F(T v) : val(v), id(false) {}
  };
  static constexpr S mapping(F f, S x) { return f.id ? x : S{pow(f.val, x.len), x.len}; }
  static constexpr F composition(F g, F f) { return g.id ? f : g; }
  static constexpr F id() { return F(); }

  static constexpr T pow(T x, size_t n) {
    T r = M::e();
    while (n) {
      if (n & 1) r = M::op(r, x);
      x = M::op(x, x);
      n >>= 1;
    }
    return r;
  }
};

} // namespace cp
