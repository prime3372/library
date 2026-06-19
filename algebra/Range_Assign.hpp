#pragma once

#include "Assign.hpp"
#include "monoid.hpp"

template <monoid M> struct Range_Assign {
  using T = typename M::S;

  struct S {
    T val;
    size_t len;
    S() : val(M::e()), len(0) {}
    S(T v, size_t l) : val(v), len(l) {}
  };
  static S op(S x, S y) { return S{M::op(x.val, y.val), x.len + y.len}; }
  static S e() { return S(); }

  using F = typename Assign<T>::F;
  static S mapping(F f, S x) { return f.id ? x : S{pow(f.val, x.len), x.len}; }
  static F composition(F g, F f) { return Assign<T>::composition(g, f); }
  static F id() { return Assign<T>::id(); }

  static T pow(T x, size_t n) {
    T r = M::e();
    while (n) {
      if (n & 1) r = M::op(r, x);
      x = M::op(x, x);
      n >>= 1;
    }
    return r;
  }

  Range_Assign() = delete;
};
