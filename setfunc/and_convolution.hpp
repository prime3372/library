#pragma once

#include <vector>

#include "superset_zeta_mobius.hpp"

namespace cp {

template <class T>
std::vector<T> and_convolution(int n, const std::vector<T>& a, const std::vector<T>& b){
  std::vector<T> za = superset_zeta(n, a);
  std::vector<T> zb = superset_zeta(n, b);
  std::vector<T> d(1 << n);
  for (int u = 0; u < (1 << n); u++) d[u] = za[u] * zb[u];
  return superset_mobius(n, d);
}

} // namespace cp