#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <utility>
#include <vector>
#include "is_prime.hpp"
#include "isqrt.hpp"

namespace internal {

// Pollard's rho algorithm
long long pollard_rho(long long n) {
  assert(2 <= n);
  if (n % 2 == 0) return 2;
  if (is_prime(n)) return n;

  static std::random_device seed_gen;
  static std::mt19937_64 mt(seed_gen());
  long long r;
  auto f = [&](__int128 x) { return (long long)((x * x + r) % n); };  

  int m = int(kth_root(n, 8));
  while (true) {
    long long x = 0, y = 0, x_tmp, y_tmp, q = 1, d = 1;
    r = mt() % (n - 2) + 2;
    while (d == 1) {
      x_tmp = x;
      y_tmp = y;
      for (int i = 0; i < m; i++) {
        x = f(x);
        y = f(f(y));
        long long z = (x - y) % n;
        q = (long long)(__int128(q) * z % n);
      }
      d = std::gcd(q, n);
    }
    if (d == n) {
      x = x_tmp;
      y = y_tmp;
      do {
        x = f(x);
        y = f(f(y));
        d = std::gcd((x - y) % n, n);
      } while (d == 1);
    }
    if (d != n) return d;
  }
}

} // namespace internal

std::vector<std::pair<long long, int>> factorize(long long n) {
  assert(1 <= n);
  if (n == 1) return {};

  std::vector<long long> fac;
  auto _factorize = [&](this auto& self, long long x) -> void {
    long long d = internal::pollard_rho(x);
    if (d == x) {
      fac.push_back(d);
      return;
    }
    self(d);
    self(x / d);
  };
  _factorize(n);
  std::sort(fac.begin(), fac.end());

  std::vector<std::pair<long long, int>> ans;
  ans.emplace_back(fac[0], 1);
  for (int i = 1; i < int(fac.size()); i++) {
    if (fac[i] == fac[i - 1]) ans.back().second++;
    else ans.emplace_back(fac[i], 1);
  }
  return ans;
}
