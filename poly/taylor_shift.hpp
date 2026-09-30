#pragma once

#include <algorithm>

#include "comb/binom_mod.hpp"
#include "poly/formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> taylor_shift(formal_power_series<mint> f, mint c) {
  // f(x+c) = sum_i f[i](x+c)^i
  //        = sum_i sum_k f[i]C(i,k)c^{i-k}x^k
  //        = sum_i sum_k f[i](i!/k!(i-k)!)c^{i-k}x^k
  //        = sum_{i-j=k} f[i](i!/k!j!)c^jx^k
  int n = int(f.size());
  binom_mod<mint> binom(n);
  formal_power_series<mint> g(n);
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