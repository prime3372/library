#pragma once

#include <cassert>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

template <class mint> requires internal::is_modint_v<mint>
class binom_mod {
 public:
  binom_mod() : binom_mod(1) {}
  explicit binom_mod(int n) : N(n) {
    assert(0 <= N);
    if (N == 0) N = 1;
    f.resize(N + 1);
    fi.resize(N + 1);
    std::vector<mint> inv(N + 1);
    inv[1] = 1;
    f[0] = f[1] = 1;
    fi[0] = fi[1] = 1;
    for (int i = 2; i <= N; i++) {
      int m = mint::mod();
      inv[i] = -inv[m % i] * (m / i);
      f[i] = f[i - 1] * i;
      fi[i] = fi[i - 1] * inv[i];
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
    assert(fi[n - r] != 0 && fi[r] != 0);
    return f[n] * fi[n - r] * fi[r];
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
    assert(fi[n - r] != 0);
    return f[n] * fi[n - r];
  }

  mint fact(int n) const {
    assert(0 <= n && n <= N);
    return f[n];
  }

  mint ifact(int n) const {
    assert(n <= N);
    if (n < 0) return 0;
    assert(fi[n] != 0);
    return fi[n];
  }

 private:
  int N;
  std::vector<mint> f, fi;
};

}  // namespace cp