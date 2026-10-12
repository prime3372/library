#pragma once

#include "poly/formal-power-series.hpp"
#include "poly/inv-of-formal-power-series.hpp"

namespace cp {

template <class mint>
FormalPowerSeries<mint> log(const FormalPowerSeries<mint>& f, int n) {
  assert(!f.empty() && f[0] == 1);
  return integral(diff(f) * inv(f, n)).prefix(n);
}

template <class mint>
FormalPowerSeries<mint> log(const FormalPowerSeries<mint>& f) {
  return log(f, int(f.size()));
}

}  // namespace cp