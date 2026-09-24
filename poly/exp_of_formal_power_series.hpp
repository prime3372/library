#pragma once

#include "poly/formal_power_series.hpp"
#include "poly/log_of_formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f, int n) {
  assert(f.empty() || f[0] == 0);
  formal_power_series<mint> g = {1};
  for (int k = 1; k < n; k *= 2) {
    g *= 1 - log(g, 2 * k) + f.prefix(2 * k);
    g.resize(2 * k);
  }
  return g.prefix(n);
}

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f) {
  return exp(f, int(f.size()));
}

}  // namespace cp