#pragma once

#include "poly/formal_power_series.hpp"
#include "poly/fps_log.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f, int n) {
  assert(f.empty() || f[0] == 0);
  formal_power_series<mint> g = {1};
  for (int d = 1; d < n; d <<= 1) {
    g = g * (1 - log(g, 2 * d) + f.prefix(2 * d));
    g.resize(2 * d);
  }
  return g.resize(n);
}

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f) {
  return exp(f, f.size());
}

}  // namespace cp