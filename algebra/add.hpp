#pragma once

namespace cp {

namespace alg {

template <class T> struct add {
  using S = T;
  static S op(S x, S y) { return x + y; }
  static S e() { return 0; }
};

}  // namespace alg

}  // namespace cp