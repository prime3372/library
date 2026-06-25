#pragma once

#include <cassert>
#include <utility>
#include <vector>

struct linear_sieve {
public:
  linear_sieve() : linear_sieve(0) {}
  explicit linear_sieve(int _n) : n(_n), f(_n + 1) {
    for (int i = 2; i <= n; i++) {
      if (!f[i]) {
        f[i] = i;
        ps.push_back(i);
      }
      for (int p : ps) {
        if (1LL * p * i > n || p > f[i]) break;
        f[p * i] = p;
      }
    }
  }

  bool is_prime(int k) const {
    assert(k <= n);
    return k < 2 ? false : f[k] == k;
  }

  const std::vector<int>& primes() const { return ps; }

  std::vector<std::pair<int, int>> factorize(int k) const {
    assert(1 <= k && k <= n);
    std::vector<std::pair<int, int>> ans;
    while (k != 1) {
      if (ans.empty() || ans.back().first != f[k]) {
        ans.emplace_back(f[k], 1);
      } else {
        ans.back().second++;
      }
      k /= f[k];
    }
    return ans;
  }

private:
  int n;
  std::vector<int> f, ps;
};
