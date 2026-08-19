#pragma once

#include <vector>

#include "setfunc/superset_zeta_mobius.hpp"

namespace cp {

template <class T>
std::vector<T> and_convolution(int n, std::vector<T> a, std::vector<T> b) {
  superset_zeta(n, a);
  superset_zeta(n, b);
  for (int i = 0; i < (1 << n); i++) a[i] *= b[i];
  superset_mobius(n, a);
  return a;
}

}  // namespace cp