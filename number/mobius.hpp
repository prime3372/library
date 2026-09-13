#pragma once

#include <cassert>

#include "number/factorize.hpp"

namespace cp {

int mobius(long long n) {
  int ans = 1;
  for (auto [p, e] : factorize(n)) {
    if (e >= 2) return 0;
    ans = -ans;
  }
  return ans;
}

} //