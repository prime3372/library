#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "factorize.hpp"

std::vector<long long> enumerate_divisors(long long n) {
  assert(1 <= n);
  std::vector<std::pair<long long, int>> fs = factorize(n);
  std::vector<long long> ans;
  auto _divisors = [&](auto self, int i, long long x) -> void {
    if (i == int(fs.size())) {
      ans.push_back(x);
      return;
    }
    self(self, i + 1, x);
    for (int j = 0; j < fs[i].second; j++) {
      self(self, i + 1, x *= fs[i].first);
    }
  };
  _divisors(_divisors, 0, 1);
  std::sort(ans.begin(), ans.end());
  return ans;
}
