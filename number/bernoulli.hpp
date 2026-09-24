#pragma once

#include <cassert>
#include <vector>

#include "comb/binom_mod.hpp"
#include "poly/formal_power_series.hpp"
#include "poly/inv_of_formal_power_series.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Bernoulli_number#Generating_function
template <class mint> std::vector<mint> bernoulli(int n) {
  assert(0 <= n);
  if (n == 0) return {1};
  binom_mod<mint> binom(n + 1);
  formal_power_series<mint> f(n + 1);
  for (int i = 0; i <= n; i++) f[i] = binom.ifact(i + 1);
  auto ans = inv(f);
  for (int i = 1; i <= n; i++) ans[i] *= binom.fact(i);
  return ans;
}

}  // namespace cp