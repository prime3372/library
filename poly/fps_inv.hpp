#pragma once

#include <algorithm>

#include "poly/formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> inv(const formal_power_series<mint>& f, int n) {
  assert(!f.empty() && f[0] != 0);
  formal_power_series<mint> g = {f[0].inv()};
  for (int d = 1; d < n; d <<= 1) {
    g = 2 * g - g * g * f.prefix(std::min(2 * d, f.size()));
    g.resize(2 * d);
  }
  return g.resize(n);
}

template <class mint>
formal_power_series<mint> inv(const formal_power_series<mint>& f) {
  return inv(f, f.size());
}

}  // namespace cp