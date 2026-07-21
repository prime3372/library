#pragma once

#include <cassert>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

template <class mint> requires (is_modint_v<mint>)
struct binom_mod {
public:
  binom_mod() : binom_mod(1) {}
  explicit binom_mod(int n) : N(n) {
    assert(0 <= N);
    if (N == 0) N = 1;
    fct.resize(N + 1);
    ifct.resize(N + 1);
    std::vector<mint> inv(N + 1);
    inv[1] = 1;
    fct[0] = fct[1] = 1;
    ifct[0] = ifct[1] = 1;
    for (int i = 2; i <= N; i++) {
      int m = mint::mod();
      inv[i] = -inv[m % i] * (m / i);
      fct[i] = fct[i - 1] * i;
      ifct[i] = ifct[i - 1] * inv[i];
    }
  }

  mint operator()(int n, int r) const {
    if (r < 0) return 0;
    if (n < 0) {
      mint res = (*this)(-n + r - 1, r);
      if (r % 2) res = -res;
      return res;
    }
    if (r > n) return 0;
    assert(n <= N);
    assert(ifct[n - r] != 0 && ifct[r] != 0);
    return fct[n] * ifct[n - r] * ifct[r];
  }

  mint perm(int n, int r) const {
    if (r < 0) return 0;
    if (n < 0) {
      mint res = perm(-n + r - 1, r);
      if (r % 2) res = -res;
      return res;
    }
    if (r > n) return 0;
    assert(n <= N);
    assert(ifct[n - r] != 0);
    return fct[n] * ifct[n - r];
  }

  mint fact(int n) const {
    assert(0 <= n && n <= N);
    return fct[n];
  }

  mint ifact(int n) const {
    assert(n <= N);
    if (n < 0) return 0;
    assert(ifct[n] != 0);
    return ifct[n];
  }

private:
  int N;
  std::vector<mint> fct, ifct;
};

} // namespace cp