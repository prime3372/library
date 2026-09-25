#pragma once

#include <cassert>
#include <vector>

#include "comb/binom_mod.hpp"
#include "poly/exp_of_formal_power_series.hpp"
#include "poly/formal_power_series.hpp"
#include "util/type_traits.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Partition_function_(number_theory)#Generating_function
template <class mint> std::vector<mint> partition(int n) {
  constexpr int m = mint::mod();
  assert(0 <= n);
  if (n == 0) return {1};
  std::vector<mint> minv(n + 1);
  minv[1] = 1;
  for (int i = 2; i <= n; i++) {
    minv[i] = -minv[m % i] * (m / i);
  }
  formal_power_series<mint> f(n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; i * j <= n; j++) {
      f[i * j] += minv[j];
    }
  }
  return exp(f);
}

}  // namespace cp