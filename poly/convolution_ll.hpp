#pragma once

#include "../number/ext_gcd.hpp"
#include "convolution.hpp"
#include "../util/static_modint.hpp"

std::vector<long long> convolution_ll(std::vector<long long> a, std::vector<long long> b) {
  int n = int(a.size()), m = int(b.size());
  if (n == 0 || m == 0) return {};
  assert(n + m - 1 <= (1 << 24));

  static constexpr long long MOD1 = 754974721;  // 45 * 2^24 + 1
  static constexpr long long MOD2 = 167772161;  //  5 * 2^25 + 1
  static constexpr long long MOD3 = 469762049;  //  7 * 2^26 + 1
  static constexpr __int128 MOD = __int128(MOD1) * MOD2 * MOD3;

  static constexpr long long i1 = inv_mod(MOD1, MOD2);
  static constexpr long long i2 = inv_mod(MOD1 * MOD2, MOD3);

  auto c1 = convolution<MOD1>(a, b);
  auto c2 = convolution<MOD2>(a, b);
  auto c3 = convolution<MOD3>(a, b);

  long long x;
  __int128 r;
  std::vector<long long> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    x = (c2[i] - c1[i]) % MOD2 * i1 % MOD2;
    if (x < 0) x += MOD2;
    c1[i] += x * MOD1;

    x = (c3[i] - c1[i]) % MOD3 * i2 % MOD3;
    if (x < 0) x += MOD3;
    r = c1[i] + __int128(x) * MOD1 * MOD2;
    if (r > MOD / 2) r -= MOD;
    c1[i] = (long long)(r);
  }
  return c1;
}
