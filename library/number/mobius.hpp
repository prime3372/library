#pragma once

#include <cassert>
#include <vector>

namespace cp {

std::vector<int> mobius(int n) {
  assert(0 <= n);
  std::vector<int> ans(n + 1, 1);
  std::vector<bool> prime(n + 1, true);
  for (int i = 2; i <= n; i++) {
    if (!prime[i]) continue;
    ans[i] = -1;
    for (long long j = 2LL * i; j <= n; j += i) {
      ans[j] *= -1;
      prime[j] = false;
    }
    for (long long j = 1LL * i * i; j <= n; j += 1LL * i * i) {
      ans[j] = 0;
    }
  }
  ans[0] = 0;
  return ans;
}

} // namespace cp