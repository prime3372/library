#pragma once

#include <cassert>
#include <vector>

std::vector<int> enumerate_primes(int n) {
  assert(0 <= n);
  std::vector<int> ps;  
  std::vector<bool> prime(n + 1, true);
  for (int i = 2; i <= n; i++) {
    if (!prime[i]) continue;
    ps.push_back(i);
    for (long long j = 1LL * i * i; j <= n; j += i) {
      prime[j] = false;
    }
  }
  return ps;
}
