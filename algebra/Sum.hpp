#pragma once

#include <cstddef>
#include "monoid.hpp"

template <class T> struct Sum {
  struct S {
    T val;
    size_t len;
    S() : val(0), len(0) {}
    S(T v, size_t l) : val(v), len(l) {}
  };
  static S op(S x, S y) { return {x.val + y.val, x.len + y.len}; }
  static S e() { return S(); }
  Range() = delete;
};
