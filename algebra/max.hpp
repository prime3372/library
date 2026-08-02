#pragma once

#include <algorithm>

namespace cp {

template <class T, T lower> struct max {
  using S = T;
  static S op(S x, S y) { return std::max(x, y); }
  static S e() { return lower; }
};

} // namespace cp