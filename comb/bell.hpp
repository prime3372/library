#pragma once

#include <cassert>
#include <vector>

#include "comb/binom_mod.hpp"
#include "poly/exp_of_formal_power_series.hpp"
#include "poly/formal_power_series.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class mint> std::vector<mint> bell(int n) {
  assert(0 <= n);
  if (n == 0) return {1};
  binom_mod<mint> binom(n);
  formal_power_series<mint> f(n + 1);
  for (int i = 1; i <= n; i++) f[i] = binom.ifact(i);
  auto ans = exp(f);
  for (int i = 1; i <= n; i++) ans[i] *= binom.fact(i);
  return ans;
}

}  // namespace cp