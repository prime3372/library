#pragma once

#include <cassert>
#include <utility>

constexpr long long pow_mod(long long x, long long n, long long m) {
  assert(0 <= n && 1 <= m);
  __int128 r = 1, y = x < 0 ? x % m + m : x % m;
  while (n) {
    if (n & 1) r = r * y % m;
    y = y * y % m;
    n >>= 1;
  }
  return (long long)r;
}
