#pragma once

#include <algorithm>
#include <cstddef>

#include "util/hash61.hpp"

namespace cp {

namespace alg {

struct rolling_hash {
  struct S {
    hash61 val, b;
    bool is_same(S other) const {
      return val == other.val;
    }
  };
  S op(S x, S y) { return {x.val * x.b + y.val, x.b * y.b}; }
  S e() { return S{0, 1}; }
};

} // namespace alg

} // namespace cp