#pragma once

#include <vector>

#include "number/ext_gcd.hpp"
#include "poly/convolution.hpp"

namespace cp {

// @note the values after convolution must be in [-2*10^18, 2*10^18]
template <class T>
std::vector<long long> convolution_ll(std::vector<T> a, std::vector<T> b) {
  int n = int(a.size()), m = int(b.size());
  if (n == 0 || m == 0) return {};

  static constexpr int MOD1 = 2130706433; // 127 * 2^24 + 1
  static constexpr int MOD2 = 2113929217; //  63 * 2^25 + 1
  static constexpr long long MOD12 = 1LL * MOD1 * MOD2;
  assert(n + m - 1 <= (1 << 24));

  static constexpr long long im = inv_mod(MOD1, MOD2);

  auto c1 = convolution<MOD1, T, long long>(a, b);
  auto c2 = convolution<MOD2, T, long long>(a, b);

  // restore the true value using CRT
  for (int i = 0; i < n + m - 1; i++) {
    long long x = (c2[i] - c1[i]) % MOD2 * im % MOD2;
    if (x < 0) x += MOD2;
    c1[i] += x * MOD1;
    if (c1[i] > MOD12 / 2) c1[i] -= MOD12;
  }
  return c1;
}

} // namespace cp