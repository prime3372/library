#pragma once

#include "monoid.hpp"

namespace cp {

template <monoid M, typename M::S identity> struct assign {
  using T = typename M::S;

  struct S {
    T val;
    size_t len;
    S() : val(M::e()), len(0) {}
    S(T v, size_t l) : val(v), len(l) {}
  };
  static constexpr S op(S x, S y) { return S{M::op(x.val, y.val), x.len + y.len}; }
  static constexpr S e() { return S(); }

  using F = typename Assign<T>::F;
  static constexpr S mapping(F f, S x) { return f == identity ? x : S{pow(f.val, x.len), x.len}; }
  static constexpr F composition(F g, F f) { return g == identity ? f : g; }
  static constexpr F id() { return identity; }

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