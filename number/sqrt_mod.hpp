#pragma once

#include "general.hpp"

// Cipolla's algorithm
constexpr long long sqrt_mod(long long a, long long p) {
  a = a < 0 ? a % p + p : a % p;
  if (a <= 1) return a;
  if (pow_mod(a, (p - 1) / 2, p) != 1) return -1;
  
  long long b = 0;
  while (pow_mod(b * b - a, (p - 1) / 2, p) == 1) b++;
  long long c = (b * b - a) % p;
  if (c < 0) c += p;
  
  struct K {
    __int128 re, im;
  };
  auto mul = [&](K x, K y) -> K {
    __int128 re = (x.re * y.re + c * x.im % p * y.im) % p;
    __int128 im = (x.re * y.im + y.re * x.im) % p;
    return K{re, im};
  };

  K x = {1, 0}, t = {b, 1};
  for (int e = (p + 1) / 2; e; e >>= 1) {
    if (e & 1) x = mul(x, t);
    t = mul(t, t);
  }
  return (long long)x.re;
}
