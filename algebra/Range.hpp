#pragma once

#include <cstddef>
#include "monoid.hpp"

template <monoid M> struct Range {
  struct S {
    typename M::S val;
    size_t len;
    S() : val(M::e()), len(0) {}
    S(typename M::S v, size_t l) : val(v), len(l) {}
  };
  static S op(S x, S y) { return {M::op(x.val, y.val), x.len + y.len}; }
  static S e() { return S(); }
  Range() = delete;
};
