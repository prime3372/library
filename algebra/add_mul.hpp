#pragma once

namespace cp {

namespace alg {

template <class T> struct add_mul {
  using S = T;
  static S op(S x, S y) { return x + y; }
  static S e() { return 0; }

  using F = T;
  static S mapping(F f, S x) { return f * x; }
  static F composition(F g, F f) { return g * f; }
  static F id() { return 1; }
};

} // namespace alg

} // namespace cp