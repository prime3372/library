#pragma once

#include "pow_mod.hpp"

// Cipolla's Algorithm
// https://en.wikipedia.org/wiki/Cipolla%27s_algorithm
constexpr long long sqrt_mod(long long n, long long p) {
  n = n < 0 ? n % p + p : n % p;
  if (n <= 1) return n;
  if (pow_mod(n, (p - 1) / 2, p) != 1) return -1;
  // if n is not a square in F_p, return -1

  long long a = 0;
  while (pow_mod(a * a - n, (p - 1) / 2, p) == 1) a++;
  // a*a - n is not a square in F_p
  // so let w = sqrt(a*a - n) and F_p^2 = F_p(w)
  long long w2 = (a * a - n) % p; 
  if (w2 < 0) w2 += p;

  struct Fp2 {
    __int128 re, im;
  };
  auto mul = [&](Fp2 x, Fp2 y) -> Fp2 {
    __int128 re = (x.re * y.re + w2 * x.im % p * y.im) % p;
    __int128 im = (x.re * y.im + y.re * x.im) % p;
    return Fp2{re, im};
  };

  Fp2 z = {1, 0}, t = {a, 1};
  for (int e = (p + 1) / 2; e; e >>= 1) {
    if (e & 1) z = mul(z, t);
    t = mul(t, t);
  }
  // [1] a^p = a (mod p) ...Fermat's little theorem
  // [2] w^(p - 1) = (w^2)^{(p - 1)/2} = -1 (mod p) ...Euler's criterion
  // [3] (x + yw)^p = x^p + y^pw^p (mod p) ...Freshman's dream
  // -> (a + w)^p = a^p - w^p = a - w (mod p)

  // z = (a + w)^{(p + 1)/2} (in F_p^2)
  // z^2 = (a + w)^(p + 1) = (a + w)(a + w)^p = (a + w)(a - w) = a^2 - w^2 = n (in F_p^2)
  // therefore z, -z are sqrt(n) in F_p^2
  // with Lagrange's theorem, polynomial of degree 2 has at most 2 roots in any field K, so z, -z are also sqrt(n) in F_p
  // note that we have already checked that n is a square in F_p

  return (long long)(z.re);
}
