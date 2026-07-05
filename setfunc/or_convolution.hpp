#pragma once

#include <vector>

#include "setfunc/subset_zeta_mobius.hpp"

namespace cp {

template <class T>
std::vector<T> or_convolution(int n, const std::vector<T>& a, const std::vector<T>& b){
  std::vector<T> za = subset_zeta(n, a);
  std::vector<T> zb = subset_zeta(n, b);
  std::vector<T> d(1 << n);
  for (int u = 0; u < (1 << n); u++) d[u] = za[u] * zb[u];
  return subset_mobius(n, d);
}

} // namespace cp