#pragma once

#include <algorithm>
#include <iostream>

namespace cp {

namespace alg {

struct bracket {
  struct S {
    int prefix_min, sum;
    bool is_correct() const {
      return prefix_min >= 0 && sum == 0;
    }
  };

  static S op(S x, S y) {
    return S{std::min(x.prefix_min, x.sum + y.prefix_min), x.sum + y.sum};
  }
  static S e() { return S{0, 0}; }
};

} // namespace alg

} // namespace cp