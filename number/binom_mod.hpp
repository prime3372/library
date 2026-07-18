#pragma once

#include <cassert>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

template <class mint> requires (is_modint_v<mint>)
struct binom_mod {
public:
  binom_mod() : binom_mod(1) {}
  explicit binom_mod(int _N) : N(_N) {
    if (_N < 1) _N = 1;
    f.resize(_N + 1);
    finv.resize(_N + 1);
    std::vector<mint> inv(_N + 1);
    inv[1] = 1;
    f[0] = f[1] = 1;
    finv[0] = finv[1] = 1;
    for (int i = 2; i <= N; i++) {
      int m = mint::mod();
      inv[i] = -inv[m % i] * (m / i);
      f[i] = f[i - 1] * i;
      finv[i] = finv[i - 1] * inv[i];
    }
  }

  mint operator()(int n, int r) const {
    assert(n <= N);
    if (n < 0 || r < 0 || n < r) return 0;
    assert(finv[n - r] != 0 && finv[r] != 0);
    return f[n] * finv[n - r] * finv[r];
  }

  mint perm(int n, int r) const {
    assert(n <= N);
    if (n < 0 || r < 0 || n < r) return 0;
    assert(finv[n - r] != 0);
    return f[n] * finv[n - r];
  }

  mint fact(int n) const {
    assert(n <= N);
    if (n < 0) return 0;
    return f[n];
  }

  mint fact_inv(int n) const {
    assert(n <= N);
    if (n < 0) return 0;
    assert(finv[n] != 0);
    return finv[n];
  }

private:
  int N;
  std::vector<mint> f, finv;
};

} // namespace cp