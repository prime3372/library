#pragma once

#include "poly/formal_power_series.hpp"
#include "poly/fps_inv.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> log(const formal_power_series<mint>& f) {
  assert(!f.empty() && f[0] == 1);
  return integ(diff(f) * inv(f)).resize(f.size());
}

}  // namespace cp