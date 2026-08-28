#pragma once

#include "poly/fps_exp.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> pow(const formal_power_series<mint>& f, long long k) {
  assert(0 <= k);
  if (f.empty()) return {};
  if (k == 0) {
    formal_power_series<mint> g(f.size());
    g[0] = 1;
    return g;
  }
  for (int i = 0; i * k < f.size(); i++) {
    if (f[i] != 0) {
      auto g = exp(log((f * f[i].inv()) >> i) * k) * f[i].pow(k);
      g <<= int(i * k);
      return g.resize(f.size());
    }
  }
  return formal_power_series<mint>(f.size());
}

}  // namespace cp