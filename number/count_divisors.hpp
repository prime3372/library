#pragma once

#include <cassert>

#include "number/factorize.hpp"

namespace cp {

// @param n `1 <= n`
long long count_divisors(long long n) {
  assert(1 <= n);
  auto factorized = factorize(n);
  long long ans = 1;
  for (auto& [p, e] : factorized) ans *= e + 1;  
  return ans;
}

}  // namespace cp