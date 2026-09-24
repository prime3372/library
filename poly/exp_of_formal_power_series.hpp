#pragma once

#include "poly/convolution.hpp"
#include "poly/formal_power_series.hpp"
#include "poly/log_of_formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f, int n) {
  assert(f.empty() || f[0] == 0);
  formal_power_series<mint> g = {1};
  for (int k = 1; k < n; k *= 2) {
    auto z = g.prefix(2 * k);
    internal::ntt(z);
    auto h = f.prefix(2 * k) - log(g, 2 * k);
    internal::ntt(h);
    for (int i = 0; i < 2 * k; i++) h[i] *= z[i];
    internal::intt(h);
    for (int i = k; i < std::min(2 * k, n); i++) g.emplace_back(h[i]);
  }
  return g;
}

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f) {
  return exp(f, int(f.size()));
}

}  // namespace cp