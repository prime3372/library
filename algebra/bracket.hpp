#pragma once

#include <algorithm>

namespace cp {

struct bracket {
  struct S {
    int prefix_min, sum;
    S() : prefix_min(0), sum(0) {}
    S(int x) : prefix_min(std::min(x, 0)), sum(x) {}
    S(int m, int s) : prefix_min(m), sum(s) {}
    bool is_good() {
      return prefix_min >= 0 && sum == 0;
    }
  };

  static S op(S x, S y) {
    return S{std::min(x.prefix_min, x.sum + y.prefix_min), x.sum + y.sum};
  }
  static S e() { return S(); }
};
} // namespace cp