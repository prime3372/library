#pragma once

#include <algorithm>

#include "poly/formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> taylor_shift(formal_power_series<mint> f, mint c) {
  int n = int(f.size()), m = mint::mod();
  if (n <= 1) return f;

  formal_power_series<mint> g(n);
  std::vector<mint> minv(n), ifact(n);
  minv[1] = 1;
  ifact[0] = ifact[1] = 1;
  for (int i = 2; i < n; i++) {
    minv[i] = -minv[m % i] * (m / i);
    ifact[i] = ifact[i - 1] * minv[i];
  }

  mint fact = 1, cpow = 1;
  g[0] = 1;
  for (int i = 1; i < n; i++) {
    fact *= i;
    cpow *= c;
    f[i] *= fact;
    g[i] = cpow * ifact[i];
  }

  std::reverse(g.begin(), g.end());
  f *= g;
  f >>= n - 1;
  for (int i = 0; i < n; i++) f[i] *= ifact[i];
  return f;
}

}  // namespace cp