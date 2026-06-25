#pragma once

#include <concepts>
#include "barrett.hpp"
#include "pow_mod.hpp"

// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
template <std::integral T> requires(sizeof(T) <= 4)
constexpr bool is_prime(T n) {
  if (n <= 2) return n == 2;
  if (n % 2 == 0) return false; 
  barrett bt((unsigned int)(n));
  long long d = (long long)(n) - 1;
  while (d % 2 == 0) d /= 2;

  for (long long a : {2, 7, 61}) {
    if (a % n == 0) continue;
    long long y = pow_mod(a, d, n);
    if (y == 1) continue;

    bool ok = false;
    for (long long t = d; t != (long long)(n) - 1; t *= 2) {
      if (y == (long long)(n) - 1) {
        ok = true;
        break;
      }
      y = bt.mul(y, y);
    }
    if (!ok) return false;
  }
  return true;
}

constexpr bool is_prime(long long n) {
  if (n <= 2) return n == 2;
  if (n % 2 == 0) return false; 
  long long d = n - 1;
  while (d % 2 == 0) d /= 2;

  for (long long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    if (a % n == 0) continue;
    __int128 y = pow_mod(a, d, n);
    if (y == 1) continue;

    bool ok = false;
    for (long long t = d; t != n - 1; t *= 2) {
      if (y == n - 1) {
        ok = true;
        break;
      }
      y = y * y % n;
    }
    if (!ok) return false;
  }
  return true;
}
