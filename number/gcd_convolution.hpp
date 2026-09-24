#pragma once

#include <cassert>
#include <vector>

#include "number/multiple_zeta_mobius.hpp"

namespace cp {

template <class T>
std::vector<T> gcd_convolution(std::vector<T> a, std::vector<T> b) {
  assert(a.size() == b.size());
  multiple_zeta(a);
  multiple_zeta(b);
  for (int i = 0; i < int(a.size()); i++) a[i] *= b[i];
  multiple_mobius(a);
  return a;
}

}  // namespace cp