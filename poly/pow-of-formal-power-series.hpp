#pragma once

#include "poly/exp-of-formal-power-series.hpp"

namespace cp {

template <class mint>
FormalPowerSeries<mint> pow(const FormalPowerSeries<mint>& f,
                            long long k,
                            int n) {
  assert(0 <= k);
  if (k == 0) return FormalPowerSeries<mint>{1}.prefix(n);
  for (int i = 0; i * k < n; i++) {
    if (f[i] != 0) {
      auto g = exp(k * log((f * f[i].inv()) >> i, n - int(i * k)));
      g *= f[i].pow(k);
      g <<= int(i * k);
      return g.prefix(n);
    }
  }
  return FormalPowerSeries<mint>(n);
}

template <class mint>
FormalPowerSeries<mint> pow(const FormalPowerSeries<mint>& f, long long k) {
  return pow(f, k, int(f.size()));
}

}  // namespace cp