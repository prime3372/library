#pragma once

#include <cassert>

#include "number/factorize.hpp"

namespace cp {

int mobius(long long n) {
  auto f = factorize(n);
  int ans = 1;
  for (auto [p, e] : f) {
    if (e >= 2) return 0;
    ans = -ans;
  }
  return ans;
}

} //