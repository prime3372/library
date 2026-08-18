#pragma once

#include <algorithm>

namespace cp {

namespace alg {

template <class T, T upper> struct min {
  using S = T;
  static S op(S x, S y) { return std::min(x, y); }
  static S e() { return upper; }
};

}  // namespace alg

}  // namespace cp