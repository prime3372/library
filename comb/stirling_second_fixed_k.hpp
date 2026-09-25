#pragma once

#include <cassert>
#include <vector>

#include "comb/binom_mod.hpp"
#include "poly/pow_of_formal_power_series.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Stirling_numbers_of_the_second_kind#Generating_functions
// @return {S(k, k), S(k+1, k), ..., S(max_n, k)}
template <class mint>
std::vector<mint> stirling_second_fixed_k(int max_n, int k) {
  assert(0 <= k && k <= max_n);
  binom_mod<mint> binom(max_n);
  formal_power_series<mint> f(max_n + 1);
  for (int i = 1; i <= max_n; i++) f[i] = binom.ifact(i);
  auto g = pow(f, k);
  for (int i = k; i <= max_n; i++) {
    g[i] *= binom.ifact(k);
    g[i] *= binom.fact(i);
  }
  return g >> k;
}

}  // namespace cp