#pragma once

#include "Assign.hpp"
#include "concepts.hpp"
#include "Range.hpp"

template <monoid M> struct Range_Assign {
  using S = typename Range<M>::S;
  static S op(S x, S y) { return Range<M>::op(x, y); }
  static S e() { return Range<M>::e(); }

  struct F = typename Assign<typename M::S>::S;
  static S mapping(F f, S x) { return f.id ? x : {pow(f.val, x.len), x.len}; }
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return Assign<typename M::S>::e(); }

  static typename M::S pow(typename M::S x, size_t n) {
    typename M::S r = M::e();
    while (n) {
      r = M::op(r, x);
      x = M::op(x, x);
      n >>= 1;
    }
    return r;
  }

  Range_Assign() = delete;
};
