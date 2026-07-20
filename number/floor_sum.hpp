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

constexpr long long floor_sum(int n, int m, long long a, long long b) {
  assert(0 <= n && 1 <= m);
  unsigned long long ans = 0;
  if (a < 0) {
    unsigned long long r_a = a < 0 ? a % m + m : a % m;
    ans -= 1ULL * n * (n - 1) / 2 * ((r_a - a) / m);
    a = r_a;
  }
  if (b < 0) {
    unsigned long long r_b = b < 0 ? b % m + m : b % m;
    ans -= 1ULL * n * ((r_b - b) / m);
    b = r_b;
  }
  return ans + internal::floor_sum_unsigned(n, m, a, b);
}

} // namespace cp