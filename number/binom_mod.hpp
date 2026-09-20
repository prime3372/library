#pragma once

#include <cassert>
#include <vector>

#include "number/is_prime.hpp"
#include "util/type_traits.hpp"

namespace cp {

// binomial coefficient mod prime
template <class mint> requires(internal::is_modint_v<mint>)
class binom_mod {
 public:
  binom_mod() : binom_mod(1) {}
  explicit binom_mod(int _n) : n(_n) {
    int m = mint::mod();
    assert(is_prime(m));
    assert(0 <= n && n < m);
    if (n == 0) {
      f[0] = finv[0] = 1;
      return;
    }
    minv.resize(n + 1);
    f.resize(n + 1);
    finv.resize(n + 1);
    minv[1] = 1;
    f[0] = f[1] = 1;
    finv[0] = finv[1] = 1;
    for (int i = 2; i <= n; i++) {
      minv[i] = -minv[m % i] * (m / i);
      f[i] = f[i - 1] * i;
      finv[i] = finv[i - 1] * minv[i];
    }
  }

  mint operator()(int k, int r) const {
    assert(0 <= k && k <= n);
    if (r < 0 || k < r) return 0;
    return f[k] * finv[k - r] * finv[r];
  }

  mint multichoose(int k, int r) const {
    if (k == 0) return r == 0;
    return (*this)(k + r - 1, r);
  }

  mint perm(int k, int r) const {
    assert(0 <= k && k <= n);
    if (r < 0 || k < r) return 0;
    return f[k] * finv[k - r];
  }

  mint inv(int k) const {
    assert(0 < k && k <= n);
    return minv[k];
  }

  mint fact(int k) const {
    assert(0 <= k && k <= n);
    return f[k];
  }

  mint ifact(int k) const {
    assert(0 <= k && k <= n);
    return finv[k];
  }

 private:
  int n;
  std::vector<mint> minv, f, finv;
};

}  // namespace cp