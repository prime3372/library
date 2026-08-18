#pragma once

#include <cassert>
#include <cmath>

namespace cp {

// @return floor(a^(1/k))
unsigned long long kth_root(unsigned long long x, unsigned long long k) {
  if (x <= 1 || k == 1) return x;
  if (64 <= k) return 1;
  auto is_small_enough = [&](unsigned __int128 y) {
    unsigned __int128 z = 1;
    unsigned long long p = k;
    while (p) {
      if (p & 1) z *= y;
      y *= y;
      p >>= 1;
    }
    return z <= x;
  };
  unsigned long long y = (unsigned long long)(std::pow(x, 1.0 / double(k)));
  while (!is_small_enough(y)) y--;
  while (is_small_enough(y + 1)) y++;
  return y;
}

}  // namespace cp