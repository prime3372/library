#pragma once

namespace cp {

template <class T> struct add {
  using S = T;
  static S op(S x, S y) { return x + y; }
  static S e() { return 0; }
  static S inv(S x) { return -x; }
};

} // namespace cp