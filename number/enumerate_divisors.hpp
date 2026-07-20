#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "number/factorize.hpp"

namespace cp {

std::vector<long long> enumerate_divisors(long long n) {
  assert(1 <= n);
  std::vector<std::pair<long long, int>> fac = factorize(n);
  std::vector<long long> ans;
  auto f = [&](auto self, int i, long long x) -> void {
    if (i == int(fac.size())) {
      ans.push_back(x);
      return;
    }
    self(self, i + 1, x);
    for (int j = 0; j < fac[i].second; j++) {
      self(self, i + 1, x *= fac[i].first);
    }
  };
  f(f, 0, 1);
  std::sort(ans.begin(), ans.end());
  return ans;
}

} // namespace cp