#pragma once

#include <algorithm>
#include <iostream>

namespace cp {

namespace alg {

struct bracket {
  struct S {
    int sum, prefix_min, suffix_max;
  };

  static S op(S x, S y) {
    return S{x.sum + y.sum, std::min(x.prefix_min, x.sum + y.prefix_min),
             std::max(x.suffix_max + y.sum, y.suffix_max)};
  }
  static S e() { return S{0, 0, 0}; }
};

}  // namespace alg

}  // namespace cp