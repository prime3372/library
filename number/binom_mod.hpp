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
  explicit binom_mod(int _n) : max_n(_n) {
    int m = mint::mod();
    assert(is_prime(m));
    assert(0 <= max_n);
    int n = (max_n == 0 ? 1 : std::min(max_n, m - 1));
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

  mint operator()(int n, int r) const {
    assert(0 <= n && n <= max_n && n < mint::mod());
    if (r < 0 || n < r) return 0;
    return f[n] * finv[n - r] * finv[r];
  }

  mint multichoose(int n, int r) const {
    if (n == 0) return r == 0;
    return (*this)(n + r - 1, r);
  }

  mint perm(int n, int r) const {
    assert(0 <= n && n <= max_n && n < mint::mod());
    if (r < 0 || n < r) return 0;
    return f[n] * finv[n - r];
  }

  mint inv(int n) const {
    assert(0 <= n && n <= max_n && n % mint::mod() != 0);
    return minv[n % mint::mod()];
  }

  mint fact(int n) const {
    assert(0 <= n && n <= max_n);
    return n < mint::mod() ? f[n] : 0;
  }

  mint ifact(int n) const {
    assert(0 <= n && n <= max_n && n < mint::mod());
    return finv[n];
  }

 private:
  int max_n;
  std::vector<mint> minv, f, finv;
};

}  // namespace cp