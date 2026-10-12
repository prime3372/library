#pragma once

#include "poly/convolution.hpp"
#include "poly/formal-power-series.hpp"
#include "poly/log-of-formal-power-series.hpp"

namespace cp {

template <class mint>
FormalPowerSeries<mint> exp(const FormalPowerSeries<mint>& f, int n) {
  assert(f.empty() || f[0] == 0);
  FormalPowerSeries<mint> g = {1};
  g.reserve(n);
  for (int k = 1; k < n; k *= 2) {
    // Newton's method:
    // g_{2*k} = g_k * (f - log(g_k) + 1) (mod x^{2*k})
    auto g2 = g.prefix(2 * k);
    auto h = f.prefix(2 * k) - log(g, 2 * k);
    internal::ntt(g2);
    internal::ntt(h);
    for (int i = 0; i < 2 * k; i++) g2[i] *= h[i];  // cyclic convolution
    internal::intt(g2);
    for (int i = k; i < std::min(2 * k, n); i++) g.emplace_back(g2[i]);
  }
  return g;
}

template <class mint>
FormalPowerSeries<mint> exp(const FormalPowerSeries<mint>& f) {
  return exp(f, int(f.size()));
}

}  // namespace cp