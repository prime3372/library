#pragma once

#include <cassert>
#include <numeric>
#include <vector>

#include "isqrt.hpp"

std::vector<long long> enumerate_quotients(long long n) {
  assert(1 <= n);
  long long r = isqrt(n);
  std::vector<long long> ans(n / (r + 1));
  std::iota(ans.begin(), ans.end(), 1);
  for (long long i = r; i >= 1; i--) {
    ans.push_back(n / i);
  }
  return ans;
}
