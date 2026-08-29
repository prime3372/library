#pragma once

#include "poly/fps_exp.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> pow(const formal_power_series<mint>& f, long long k,
                              int n) {
  assert(0 <= k);
  if (k == 0) {
    formal_power_series<mint> g = {1};
    return g.resize(n);
  }
  for (int i = 0; i * k < n; i++) {
    if (f[i] != 0) {
      auto g = exp(log((f * f[i].inv()) >> i, n - int(i * k)) * k);
      g *= f[i].pow(k);
      g <<= int(i * k);
      return g.resize(n);
    }
  }
  return formal_power_series<mint>(n);
}

template <class mint>
formal_power_series<mint> pow(const formal_power_series<mint>& f, long long k) {
  return pow(f, k, f.size());
}

}  // namespace cp