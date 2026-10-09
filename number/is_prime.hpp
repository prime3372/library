#pragma once

#include <array>

#include "number/barrett.hpp"
#include "number/pow_mod.hpp"

namespace cp {

// Miller–Rabin primality test
// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
// https://docslib.org/doc/5395180/fast-primality-testing-for-integers-that-fit-into-a-machine-word
bool is_prime(long long n) {
  if (n <= 2) return n == 2;
  if (n % 2 == 0) return false;

  int base_num;
  std::array<long long, 7> bases;
  if (n < 4759123141) {
    base_num = 3;
    bases = {2, 7, 61};
  } else {
    base_num = 7;
    bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  }

  long long d = n - 1;
  while (d % 2 == 0) d /= 2;
  for (int i = 0; i < base_num; i++) {
    long long a = bases[i];
    if (a % n == 0) continue;
    __int128 x = pow_mod(a, d, n);
    long long t = d;
    while (t != n - 1 && x != 1 && x != n - 1) {
      x = x * x % n;
      t *= 2;
    }
    if (x != n - 1 && t % 2 == 0) return false;
  }
  return true;
}

}  // namespace cp