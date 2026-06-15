#pragma once

#include <cassert>
#include <numeric>

std::vector<int> totient(int n) {
  assert(0 <= n);
  std::vector<int> ans(n + 1);
  std::iota(ans.begin(), ans.end(), 0);
  for (int i = 2; i <= n; i++) {
    if (ans[i] != i) continue;
    for (long long j = i; j <= n; j += i) {
      ans[j] = ans[j] / i * (i - 1);
    }
  }
  return ans;
}
