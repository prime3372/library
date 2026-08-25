#pragma once

#include <cassert>
#include <vector>

namespace cp {

// @param n `0 <= n`
std::vector<int> enumerate_primes(int n) {
  assert(0 <= n);
  std::vector<int> ans;
  std::vector<bool> sieve(n + 1, true);
  for (int i = 2; i <= n; i++) {
    if (!sieve[i]) continue;
    ans.push_back(i);
    for (long long j = 1LL * i * i; j <= n; j += i) {
      sieve[j] = false;
    }
  }
  return ans;
}

}  // namespace cp