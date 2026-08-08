#pragma once

#include <vector>

#include "number/pow_mod.hpp"

namespace cp {

namespace internal {

constexpr int primitive_root_constexpr(int p) {
  if (p == 2) return 1;

  std::vector<int> fac = {2};
  int x = p - 1;
  while (x % 2 == 0) x /= 2;
  for (int i = 3; 1LL * i * i <= x; i += 2) {
    if (x % i == 0) {
      fac.push_back(i);
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) fac.push_back(x);

  for (int g = 2;; g++) {
    bool ok = true;
    for (int f : fac) {
      if (pow_mod(g, (p - 1) / f, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}

} // namespace internal

} // namespace cp