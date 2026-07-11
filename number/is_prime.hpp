#pragma once

#include <concepts>
#include <vector>

#include "number/barrett.hpp"
#include "number/pow_mod.hpp"

namespace cp {

// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
constexpr bool is_prime(long long n) {
  if (n <= 2) return n == 2;
  if (n % 2 == 0) return false; 
  long long d = n - 1;
  while (d % 2 == 0) d /= 2;

  std::vector<long long> bases;
  if (n < 4759123141) bases = {2, 7, 61};
  else bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

  for (long long a : bases) {
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

} // namespace cp