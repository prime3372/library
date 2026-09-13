#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

#include "number/is_prime.hpp"
#include "number/kth_root.hpp"
#include "random/engine.hpp"
#include "util/run_length_encoding.hpp"

namespace cp {

// Pollard's Rho Algorithm
// @param n `2 <= n`
long long pollard_rho(long long n) {
  assert(2 <= n);
  if (n % 2 == 0) return 2;
  if (is_prime(n)) return n;

  long long c;
  auto f = [&](__int128 x) { return (long long)((x * x + c) % n); };

  int r = int(kth_root(n, 8));
  while (true) {
    long long x = 0, y = 0, sx, sy, q = 1, d = 1;
    c = uniform(2LL, n - 1);
    while (d == 1) {
      sx = x;
      sy = y;
      for (int i = 0; i < r; i++) {
        x = f(x);
        y = f(f(y));
        long long z = (x - y) % n;
        q = (long long)(__int128(q) * z % n);
      }
      d = std::gcd(q, n);
    }
    if (d == n) {
      x = sx;
      y = sy;
      do {
        x = f(x);
        y = f(f(y));
        d = std::gcd((x - y) % n, n);
      } while (d == 1);
    }
    if (d != n) return d;
  }
}

// @param n `1 <= n`
std::vector<std::pair<long long, int>> factorize(long long n) {
  assert(1 <= n);
  if (n == 1) return {};
  std::vector<long long> factors;
  auto f = [&](auto self, long long x) -> void {
    long long d = pollard_rho(x);
    if (d == x) {
      factors.push_back(d);
      return;
    }
    self(self, d);
    self(self, x / d);
  };
  f(f, n);
  std::sort(factors.begin(), factors.end());
  return run_length_encoding(factors);
}

}  // namespace cp