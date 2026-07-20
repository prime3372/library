#pragma once

#include <cassert>
#include <utility>

namespace cp {

// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<long long, long long> ext_gcd(long long a, long long b) {
  assert(1 <= b);
  a %= b;
  if (a < 0) a += b;
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
  assert(1 <= m);
  auto z = ext_gcd(x, m);
  assert(z.first == 1);
  return z.second;
}

} // namespace cp