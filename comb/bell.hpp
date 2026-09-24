#pragma once

#include <vector>

#include "poly/exp_of_formal_power_series.hpp"
#include "poly/formal_power_series.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class mint> requires(internal::is_static_modint_v<mint>)
std::vector<mint> bell(int n) {
  constexpr int m = mint::mod();
  if (n == 0) return {1};
  std::vector<mint> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = -inv[m % i] * (m / i);
  }
  mint ifact = 1;
  formal_power_series<mint> fps(n + 1);
  for (int i = 1; i <= n; i++) {
    ifact *= inv[i];
    fps[i] = ifact;
  }
  mint fact = 1;
  auto ans = exp(fps);
  for (int i = 1; i <= n; i++) {
    fact *= i;
    ans[i] *= fact;
  }
  return ans;
}

}  // namespace cp