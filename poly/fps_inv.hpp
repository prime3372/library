#pragma once

#include "poly/formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> inv(const formal_power_series<mint>& f) {
  assert(!f.empty() && f[0] != 0);
  formal_power_series<mint> g = {f[0].inv()};
  for (int d = 1; d < f.size(); d <<= 1) {
    g = 2 * g - g * g * f.prefix(2 * d);
    g.resize(2 * d);
  }
  return g.resize(f.size());
}

}  // namespace cp