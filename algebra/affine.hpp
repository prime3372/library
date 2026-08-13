#pragma once

#include <iostream>

namespace cp {

namespace alg {

template <class T> struct affine {
  struct S {
    T a = 1, b = 0;

    T operator()(T x) const { return a * x + b; }

    friend std::ostream& operator<<(std::ostream& os, const S& x) {
      os << x.a << "x + " << x.b;
      return os;
    }
  };
  static S op(S f, S g) { return S{g.a * f.a, g.a * f.b + g.b}; }
  static S e() { return S(); }
};

} // namespace alg

} // namespace cp