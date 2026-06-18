#pragma once

#include <cassert>
#include <concepts>
#include <utility>
#include <type_traits>
#include "barrett.hpp"

template <std::integral Mod> requires (sizeof(Mod) <= 4)
constexpr long long pow_mod(long long x, long long n, Mod m) {
  assert(0 <= n && 1 <= m);
  if consteval {
    long long r = 1, y = x < 0 ? x % m + m : x % m;
    while (n) {
      if (n & 1) r = r * y % m;
      y = y * y % m;
      n >>= 1;
    }
    return r;
  } else {
    if (m == 1) return 0;
    barrett bt((unsigned int)(m));
    x = x < 0 ? x % m + m : x % m;
    unsigned int r = 1, y = (unsigned int)(x);
    while (n) {
      if (n & 1) r = bt.mul(r, y);
      y = bt.mul(y, y);
      n >>= 1;
    }
    return r;
  }
}

constexpr long long pow_mod(long long x, long long n, long long m) {
  assert(0 <= n && 1 <= m);
  __int128 r = 1, y = x < 0 ? x % m + m : x % m;
  while (n) {
    if (n & 1) r = r * y % m;
    y = y * y % m;
    n >>= 1;
  }
  return (long long)(r);
}
