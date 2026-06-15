#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <utility>
#include <vector>
#include "general.hpp"
#include "is_prime.hpp"

namespace internal {

// Pollard's rho algorithm
long long pollard_rho(long long n) {
  if (n % 2 == 0) return 2;
  if (is_prime(n)) return n;

  static std::random_device seed_gen;
  static std::mt19937_64 mt(seed_gen());
  long long r;
  auto f = [&](__int128 x) { return (long long)((x * x + r) % n); };  

  int m = int(kth_root(n, 8));
  while (true) {
    long long x = 0, y = 0, x_tmp, y_tmp, q = 1, g = 1;
    r = mt() % (n - 2) + 2;
    while (g == 1) {
      x_tmp = x;
      y_tmp = y;
      for (int i = 0; i < m; i++) {
        x = f(x);
        y = f(f(y));
        long long d = (x - y) % n;
        q = (long long)(__int128(q) * d % n);
      }
      g = std::gcd(q, n);
    }
    if (g == n) {
      x = x_tmp;
      y = y_tmp;
      do {
        x = f(x);
        y = f(f(y));
        g = std::gcd((x - y) % n, n);
      } while (g == 1);
    }
    if (g != n) return g;
  }
}

}

std::vector<std::pair<long long, int>> factorize(long long n) {
  assert(1 <= n);
  if (n == 1) return {};

  std::vector<long long> fac;
  auto _factorize = [&](auto self, long long x) -> void {
    long long d = internal::pollard_rho(x);
    if (d == x) {
      fac.push_back(d);
      return;
    }
    self(self, d);
    self(self, x / d);
  };
  _factorize(_factorize, n);
  std::sort(fac.begin(), fac.end());

  std::vector<std::pair<long long, int>> ans;
  ans.emplace_back(fac[0], 1);
  for (int i = 1; i < int(fac.size()); i++) {
    if (fac[i] == fac[i - 1]) ans.back().second++;
    else ans.emplace_back(fac[i], 1);
  }
  return ans;
}

std::vector<long long> divisors(long long n) {
  assert(1 <= n);
  std::vector<std::pair<long long, int>> fs = factorize(n);
  std::vector<long long> ans;
  auto _divisors = [&](auto self, int i, long long x) -> void {
    if (i == int(fs.size())) {
      ans.push_back(x);
      return;
    }
    self(self, i + 1, x);
    for (int j = 0; j < fs[i].second; j++) {
      self(self, i + 1, x *= fs[i].first);
    }
  };
  _divisors(_divisors, 0, 1);
  std::sort(ans.begin(), ans.end());
  return ans;
}
