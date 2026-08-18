#pragma once

#include <array>

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

  int base_num;
  std::array<long long, 7> bases;
  if (n < 4759123141) {
    base_num = 3;
    bases = {2, 7, 61};
  } else {
    base_num = 7;
    bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  }

  for (int i = 0; i < base_num; i++) {
    long long a = bases[i];
    if (a % n == 0) continue;
    long long t = d;
    __int128 y = pow_mod(a, d, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = y * y % n;
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) return false;
  }
  return true;
}

}  // namespace cp