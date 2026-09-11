#pragma once

#include <cassert>
#include <vector>

#include "number/is_prime.hpp"
#include "util/type_traits.hpp"

namespace cp {

// @note The mod must be prime.
template <class mint> requires(internal::is_modint_v<mint>)
class binom_mod {
 public:
  binom_mod() : binom_mod(1) {}
  explicit binom_mod(int n) : N(n) {
    static int m = mint::mod();
    assert(is_prime(m));
    assert(0 <= N && N < m);
    int K = std::max(N, 1);
    f.resize(K + 1);
    fi.resize(K + 1);
    std::vector<mint> inv(K + 1);
    inv[1] = 1;
    f[0] = f[1] = 1;
    fi[0] = fi[1] = 1;
    for (int i = 2; i <= K; i++) {
      inv[i] = -inv[m % i] * (m / i);
      f[i] = f[i - 1] * i;
      fi[i] = fi[i - 1] * inv[i];
    }
  }

  mint operator()(int n, int r) const {
    assert(0 <= n && n <= N);
    if (r < 0 || n < r) return 0;
    return f[n] * fi[n - r] * fi[r];
  }

  mint multichoose(int n, int r) const {
    assert(0 <= n && n + r - 1 <= N);
    if (n == 0) return r == 0;
    if (r < 0) return 0;
    return (*this)(n + r - 1, r);
  }

  mint perm(int n, int r) const {
    assert(0 <= n && n <= N);
    if (r < 0 || n < r) return 0;
    return f[n] * fi[n - r];
  }

  mint fact(int n) const {
    assert(0 <= n && n <= N);
    return f[n];
  }

  mint ifact(int n) const {
    assert(0 <= n && n <= N);
    return fi[n];
  }

 private:
  int N;
  std::vector<mint> f, fi;
};

}  // namespace cp