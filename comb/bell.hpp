#pragma once

#include <cassert>
#include <vector>

#include "comb/binom-mod.hpp"
#include "poly/exp-of-formal-power-series.hpp"
#include "poly/formal-power-series.hpp"
#include "util/type-traits.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Bell_number#Generating_function
template <class mint> std::vector<mint> bell(int n) {
  assert(0 <= n);
  if (n == 0) return {1};
  BinomMod<mint> binom(n);
  FormalPowerSeries<mint> f(n + 1);
  for (int i = 1; i <= n; i++) f[i] = binom.ifact(i);
  auto ans = exp(f);
  for (int i = 1; i <= n; i++) ans[i] *= binom.fact(i);
  return ans;
}

}  // namespace cp