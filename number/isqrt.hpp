#pragma once

#include <cassert>
#include <cmath>

constexpr unsigned long long isqrt(unsigned long long x) {
  unsigned long long y = (unsigned long long)std::sqrt(x);
  while (y && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

constexpr unsigned long long icbrt(unsigned long long x) {
  unsigned long long y = (unsigned long long)std::cbrt(x);
  while (y && y * y > x / y) y--;
  while ((y + 1) * (y + 1) <= x / (y + 1)) y++;
  return y;
}

constexpr unsigned long long kth_root(unsigned long long x, int k) {
  assert(k);
  if (x <= 1 || k == 1) return x;
  if (64 <= k) return 1;
  auto check = [&](unsigned __int128 y) {
    unsigned __int128 z = 1;
    for (int e = k; e; e >>= 1) {
      if (e & 1) z *= y;
      y *= y;
    }
    return z <= x;
  };
  unsigned long long y = (unsigned long long)std::pow(x, 1.0 / k);
  while (!check(y)) y--;
  while (check(y + 1)) y++;
  return y;
}
