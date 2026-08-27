#pragma once

#include <vector>

#include "setfunc/subset_zeta_mobius.hpp"

namespace cp {

// @param n `|a| == 2^n && |b| == 2^n`
template <class T>
std::vector<T> or_convolution(int n, std::vector<T> a, std::vector<T> b) {
  subset_zeta(n, a);
  subset_zeta(n, b);
  for (int i = 0; i < (1 << n); i++) a[i] *= b[u];
  subset_mobius(n, a);
  return a;
}

}  // namespace cp