#pragma once

#include <algorithm>

#include "poly/convolution.hpp"
#include "poly/formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> inv(const formal_power_series<mint>& f, int n) {
  assert(!f.empty() && f[0] != 0);
  formal_power_series<mint> g = {f[0].inv()};
  g.reserve(n);
  for (int k = 1; k < n; k *= 2) {
    // Newton's method:
    // g_{2*k} = 2 * g_k - g_k * g_k * f (mod x^{2*k})
    auto f2 = f.prefix(2 * k);
    auto g2 = g.prefix(2 * k);
    internal::ntt(f2);
    internal::ntt(g2);
    for (int i = 0; i < 2 * k; i++) f2[i] *= g2[i];  // cyclic convolution
    internal::intt(f2);
    for (int i = 0; i < k - 1; i++) f2[i] = 0;  // g_k * f = 1 (mod x^k)
    internal::ntt(f2);
    for (int i = 0; i < 2 * k; i++) f2[i] *= g2[i];  // cyclic convolution
    internal::intt(f2);
    for (int i = k; i < std::min(n, 2 * k); i++) g.emplace_back(-f2[i]);
  }
  return g;
}

template <class mint>
formal_power_series<mint> inv(const formal_power_series<mint>& f) {
  return inv(f, int(f.size()));
}

}  // namespace cp