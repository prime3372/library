#pragma once

#include <cassert>
#include <concepts>
#include <utility>
#include <type_traits>

#include "number/barrett.hpp"

namespace cp {

constexpr long long pow_mod(long long x, long long n, long long m) {
  assert(0 <= n && 1 <= m);
  if (m == 1) return 0;

  if (m >> 32) {
    __int128 r = 1, y = x % m;
    if (y < 0) y += m;
    while (n) {
      if (n & 1) r = r * y % m;
      y = y * y % m;
      n >>= 1;
    }
    return (long long)(r);
  }

  barrett bt((unsigned int)(m));
  x %= m;
  if (x < 0) x += m;
  unsigned int r = 1, y = (unsigned int)(x);
  while (n) {
    if (n & 1) r = bt.mul(r, y);
    y = bt.mul(y, y);
    n >>= 1;
  }
  return r;
}

} // namespace cp