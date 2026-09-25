#pragma once

#include <cassert>
#include <vector>

#include "comb/binom_mod.hpp"
#include "poly/formal_power_series.hpp"
#include "poly/pow_of_formal_power_series.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Stirling_numbers_of_the_first_kind#Generating_functions
// @return {s(k, k), s(k+1, k), ..., s(max_n, k)}
template <class mint>
std::vector<mint> stirling_first_kind_fixed_k(int k, int max_n) {
  assert(0 <= k && k <= max_n);
  binom_mod<mint> binom(max_n);
  formal_power_series<mint> f(max_n + 1);
  for (int i = 1; i <= max_n; i++) f[i] = (i % 2 ? 1 : -1) * binom.inv(i);
  auto g = pow(f, k);
  for (int i = k; i <= max_n; i++) {
    g[i] *= binom.ifact(k);
    g[i] *= binom.fact(i);
  }
  return g >> k;
}

// https://en.wikipedia.org/wiki/Stirling_numbers_of_the_first_kind#Generating_functions
// @return {c(k, k), c(k+1, k), ..., c(max_n, k)}
template <class mint>
std::vector<mint> unsigned_stirling_first_kind_fixed_k(int k, int max_n) {
  assert(0 <= k && k <= max_n);
  binom_mod<mint> binom(max_n);
  formal_power_series<mint> f(max_n + 1);
  for (int i = 1; i <= max_n; i++) f[i] = binom.inv(i);
  auto g = pow(f, k);
  for (int i = k; i <= max_n; i++) {
    g[i] *= binom.ifact(k);
    g[i] *= binom.fact(i);
  }
  return g >> k;
}
}  // namespace cp