#pragma once

#include <cstddef>
#include <iostream>

#include "util/io_utility.hpp"

namespace cp {

template <class M> struct assign {
  using T = typename M::S;

  struct S {
    T val;
    size_t len;
    S() : val(M::e()), len(0) {}
    S(T v) : val(v), len(1) {}
    S(T v, size_t l) : val(v), len(l) {}

    friend std::ostream& operator<<(std::ostream& os, const S& x) {
      os << x.val;
      return os;
    }
  };
  static S op(S x, S y) { return S{M::op(x.val, y.val), x.len + y.len}; }
  static S e() { return S(); }

  struct F {
    T val;
    bool id;
    F() : val(), id(true) {}
    F(T v) : val(v), id(false) {}
  };
  static S mapping(F f, S x) { return f.id ? x : S{pow(f.val, x.len), x.len}; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return F(); }

  static T pow(T x, size_t n) {
    T r = M::e();
    while (n) {
      if (n & 1) r = M::op(r, x);
      x = M::op(x, x);
      n >>= 1;
    }
    return r;
  }
};

namespace internal {

template <class M> struct delimiter<typename assign<M>::S> {
  static constexpr char value[] = " ";
};

} // namespace internal

} // namespace cp