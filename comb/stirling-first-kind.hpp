#pragma once

#include <cassert>
#include <vector>

#include "poly/formal-power-series.hpp"
#include "poly/taylor-shift.hpp"

namespace cp {

namespace internal {

template <class mint>
FormalPowerSeries<mint> signed_stirling_first_kind_recursive(int n) {
  if (n == 0) return {1};
  if (n == 1) return {0, 1};
  auto f = signed_stirling_first_kind_recursive<mint>(n / 2);
  auto g = taylor_shift(f, -mint(n / 2));
  f *= g;
  if (n % 2) f *= {1 - n, 1};
  return f;
}

}  // namespace internal

// s(n,k) = [x^k]x(x-1)...(x-n+1)
template <class mint> std::vector<mint> signed_stirling_first_kind(int n) {
  assert(0 <= n);
  return internal::signed_stirling_first_kind_recursive<mint>(n);
}

// c(n,k) = [x^k]x(x+1)...(x+n-1)
template <class mint> std::vector<mint> unsigned_stirling_first_kind(int n) {
  assert(0 <= n);
  auto s = signed_stirling_first_kind<mint>(n);
  for (int i = n - 1; i >= 0; i -= 2) s[i] = -s[i];
  return s;
}

}  // namespace cp