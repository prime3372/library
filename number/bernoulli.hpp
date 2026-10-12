#pragma once

#include <cassert>
#include <vector>

#include "comb/binom-mod.hpp"
#include "poly/formal-power-series.hpp"
#include "poly/inv-of-formal-power-series.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Bernoulli_number#Generating_function
template <class mint> std::vector<mint> bernoulli(int n) {
  assert(0 <= n);
  if (n == 0) return {1};
  binom_mod<mint> binom(n + 1);
  FormalPowerSeries<mint> f(n + 1);
  for (int i = 0; i <= n; i++) f[i] = binom.ifact(i + 1);
  auto ans = inv(f);
  for (int i = 1; i <= n; i++) ans[i] *= binom.fact(i);
  return ans;
}

}  // namespace cp