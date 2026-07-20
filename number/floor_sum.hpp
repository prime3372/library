#pragma once

#include <cassert>
#include <utility>

namespace cp {

namespace internal {

constexpr unsigned long long floor_sum_unsigned(unsigned long long n,
                                                unsigned long long m,
                                                unsigned long long a,
                                                unsigned long long b) {
  unsigned long long ans = 0;
  while (true) {
    if (a >= m) {
      ans += n * (n - 1) / 2 * (a / m);
      a %= m;
    }
    if (b >= m) {
      ans += n * (b / m);
      b %= m;
    }

    unsigned long long y = a * n + b;
    if (y < m) break;
    n = y / m;
    b = y % m;
    std::swap(a, m);
  }
  return ans;
}

} // namespace internal

constexpr long long floor_sum(long long n, long long m, long long a, long long b) {
  assert(0 <= n && n < 1LL << 32);
  assert(1 <= m && m < 1LL << 32); 
  unsigned long long ans = 0;
  if (a < 0) {
    unsigned long long a2 = a % m + m;
    ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
    a = a2;
  }
  if (b < 0) {
    unsigned long long b2 = b % m + m;
    ans -= 1ULL * n * ((b2 - b) / m);
    b = b2;
  }
  return ans + internal::floor_sum_unsigned(n, m, a, b);
}

} // namespace cp