#pragma once

#include <cassert>
#include "factorize.hpp"

constexpr long long primitive_root(long long p) {
  if (p == 2) return 1;  
  auto fs = factorize(p - 1);
  for (int g = 2; g < p; g++) {
    bool ok = true;
    for (auto f : fs) {
      if (pow_mod(g, (p - 1) / f.first, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
  assert(false);
}
