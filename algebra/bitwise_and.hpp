#pragma once

namespace cp {

template <class T> struct bitwise_and {
  using S = T;
  static S op(S x, S y) { return x & y; }
  static S e() { return -1; }
};

} // namespace cp