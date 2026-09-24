#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "number/factorize.hpp"

namespace cp {

// @param n `1 <= n`
std::vector<long long> enumerate_divisors(long long n) {
  assert(1 <= n);
  auto f = factorize(n);
  long long cnt = 1;
  for (auto [p, e] : f) cnt *= e + 1;
  std::vector<long long> ans = {1};
  ans.reserve(cnt);
  for (auto [p, e] : f) {
    int sz = int(ans.size());
    long long cur = 1;
    for (int i = 0; i < e; i++) {
      cur *= p;
      for (int j = 0; j < sz; j++) {
        ans.push_back(ans[j] * cur);
      }
    }
  }
  sort(ans.begin(), ans.end());
  return ans;
}

}  // namespace cp