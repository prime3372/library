#pragma once

#include <algorithm>

#include "comb/binom-mod.hpp"
#include "poly/formal-power-series.hpp"

namespace cp {

template <class mint>
FormalPowerSeries<mint> taylor_shift(FormalPowerSeries<mint> f, mint c) {
  // f(x+c) = sum_i f[i](x+c)^i
  //        = sum_i sum_k f[i]C(i,k)c^{i-k}x^k
  //        = sum_i sum_k f[i](i!/k!(i-k)!)c^{i-k}x^k
  //        = sum_{i-j=k} f[i](i!/k!j!)c^jx^k

  int n = int(f.size());
  BinomMod<mint> binom(n);
  FormalPowerSeries<mint> g(n);
  mint cpow = 1;
  g[0] = 1;
  for (int i = 1; i < n; i++) {
    cpow *= c;
    f[i] *= binom.fact(i);
    g[i] = cpow * binom.ifact(i);
  }
  std::reverse(g.begin(), g.end());
  f *= g;
  f >>= n - 1;
  for (int i = 0; i < n; i++) f[i] *= binom.ifact(i);
  return f;
}

}  // namespace cp