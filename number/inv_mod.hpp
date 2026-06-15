#pragma once

#include <cassert>
#include <utility>

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
  assert(1 <= b);
  a = a < 0 ? a % b + b : a % b;
  long long g0 = b, g1 = a;
  long long x0 = 0, x1 = 1;
  while (g1) {
    long long q = g0 / g1;
    g0 -= g1 * q;
    x0 -= x1 * q;
    std::swap(g0, g1);
    std::swap(x0, x1);
  }
  if (x0 < 0) x0 += b / g0;
  return {g0, x0};
}

constexpr long long inv_mod(long long x, long long m) {
  assert(2 <= m);
  auto z = inv_gcd(x, m);
  assert(z.first == 1);
  return z.second;
}
