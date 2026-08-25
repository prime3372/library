#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "number/factorize.hpp"

namespace cp {

// @param n `1 <= n`
// @note The order of the divisors is undefined.
std::vector<long long> enumerate_divisors(long long n) {
  assert(1 <= n);
  std::vector<std::pair<long long, int>> fac = factorize(n);
  std::vector<long long> ans;
  auto enumerate = [&](auto self, int i, long long d) -> void {
    if (i == int(fac.size())) {
      ans.push_back(d);
      return;
    }
    self(self, i + 1, d);
    for (int j = 0; j < fac[i].second; j++) {
      self(self, i + 1, d *= fac[i].first);
    }
  };
  enumerate(enumerate, 0, 1);
  return ans;
}

}  // namespace cp