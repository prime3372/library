#pragma once

#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>

#include "util/math_utility.hpp"

namespace cp {

// @param n `1 <= n`
// @return vector of (q,l,r) s.t. q is a quotient and [n/i]=d <=> l<=d<r
std::vector<std::array<long long, 3>> enumerate_quotients(long long n) {
  assert(1 <= n);
  long long r = isqrt(n);
  std::vector<long long> quots(n / (r + 1));
  std::iota(quots.begin(), quots.end(), 1);
  quots.reserve(n / (r + 1) + r);
  for (long long i = r; i >= 1; i--) quots.push_back(n / i);
  std::vector<std::array<long long, 3>> ans(n / (r + 1) + r);
  for (int i = 0; i < n / (r + 1) + r; i++) {
    ans[i][0] = quots[i];
    ans[i][1] = n / (quots[i] + 1) + 1;
    ans[i][2] = n / quots[i] + 1;
  }
  return ans;
}

}  // namespace cp