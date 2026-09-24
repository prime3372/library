#pragma once

#include <cassert>
#include <vector>

#include "poly/exp_of_formal_power_series.hpp"
#include "poly/formal_power_series.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class mint> std::vector<mint> bell(int n) {
  constexpr int m = mint::mod();
  assert(0 <= n);
  if (n == 0) return {1};
  std::vector<mint> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = -inv[m % i] * (m / i);
  }
  mint ifact = 1;
  formal_power_series<mint> f(n + 1);
  for (int i = 1; i <= n; i++) {
    ifact *= inv[i];
    f[i] = ifact;
  }
  auto ans = exp(f);
  mint fact = 1;
  for (int i = 1; i <= n; i++) ans[i] *= (fact *= i);
  return ans;
}

}  // namespace cp