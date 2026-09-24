#pragma once

#include <cassert>
#include <vector>

#include "number/divisor_zeta_mobius.hpp"

namespace cp {

template <class T>
std::vector<T> lcm_convolution(std::vector<T> a, std::vector<T> b) {
  assert(a.size() == b.size());
  divisor_zeta(a);
  divisor_zeta(b);
  for (int i = 0; i < int(a.size()); i++) a[i] *= b[i];
  divisor_mobius(a);
  return a;
}

}  // namespace cp