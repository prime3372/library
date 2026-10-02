#pragma once

#include <cassert>
#include <vector>

#include "comb/binom_mod.hpp"
#include "poly/formal_power_series.hpp"
#include "poly/inv_of_formal_power_series.hpp"
#include "util/type_traits.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Partition_function_(number_theory)#Generating_function
template <class mint> std::vector<mint> partition(int n) {
  assert(0 <= n);
  if (n == 0) return {1};
  formal_power_series<mint> f(n + 1);
  for (int i = 0; 1LL * i * (3 * i - 1) / 2 <= n; i++) {
    f[i * (3 * i - 1) / 2] = (i % 2 ? -1 : 1);
  }
  for (int i = -1; 1LL * i * (3 * i - 1) / 2 <= n; i--) {
    f[i * (3 * i - 1) / 2] = (i % 2 ? -1 : 1);
  }
  return inv(f);
}

}  // namespace cp