#pragma once

#include <cstddef>
#include <iostream>

namespace cp {

namespace alg {

template <class M> struct assign {
  using T = typename M::S;

  struct S {
    T val;
    size_t len;

    // for debugging
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
  };
  static S mapping(F f, S x) { return f.id ? x : S{pow(f.val, x.len), x.len}; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return F{T(), true}; }

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

} // namespace alg

} // namespace cp