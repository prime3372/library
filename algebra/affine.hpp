#pragma once

#include <iostream>

namespace cp {

template <class T> struct affine {
  struct S {
    T a, b;
    S() : a(1), b(0) {}
    S(T _a, T _b) : a(_a), b(_b) {}

    // for debugging
    friend std::ostream& operator<<(std::ostream& os, const S& x) {
      os << "(a: " << x.a << " b: " << x.b << ")";
      return os;
    }
  };
  static S op(S f, S g) { return {g.a * f.a, g.a * f.b + g.b}; }
  static S e() { return S(); }
  static S inv(S f) {
    return S{1 / f.a, -f.b / f.a};
  }
};

} // namespace cp