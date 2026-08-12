#pragma once

#include <iostream>

namespace cp {

namespace alg {

template <class T> struct affine {
  struct S {
    T a = 1, b = 0;

    T operator()(T x) const { return a * x + b; }

    // for debugging
    friend std::ostream& operator<<(std::ostream& os, const S& x) {
      if (x.a == 0) os << x.b;
      else if (x.a == 1) os << "x + " << x.b;
      else os << x.a << "x + " << x.b;
      return os;
    }
  };
  static S op(S f, S g) { return S{g.a * f.a, g.a * f.b + g.b}; }
  static S e() { return S(); }
};

} // namespace alg

} // namespace cp