#pragma once

#include <cassert>
#include <vector>

#include "comb/binom-mod.hpp"
#include "poly/pow-of-formal-power-series.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Stirling_numbers_of_the_second_kind#Generating_functions
// @return {S(k, k), S(k+1, k), ..., S(max_n, k)}
template <class mint>
std::vector<mint> stirling_second_kind_fixed_k(int k, int max_n) {
  assert(0 <= k && k <= max_n);
  BinomMod<mint> binom(max_n);
  FormalPowerSeries<mint> f(max_n + 1);
  for (int i = 1; i <= max_n; i++) f[i] = binom.ifact(i);
  auto g = pow(f, k);
  for (int i = k; i <= max_n; i++) {
    g[i] *= binom.ifact(k);
    g[i] *= binom.fact(i);
  }
  return g >> k;
}

}  // namespace cp