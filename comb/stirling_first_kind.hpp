#pragma once

#include <cassert>
#include <vector>

#include "poly/formal_power_series.hpp"
#include "poly/taylor_shift.hpp"

namespace cp {

namespace internal {

template <class mint>
formal_power_series<mint> stirling_first_kind_recursive(int n) {
  if (n == 0) return {1};
  if (n == 1) return {0, 1};
  auto f = stirling_first_kind_recursive<mint>(n / 2);
  auto g = taylor_shift(f, -mint(n / 2));
  f *= g;
  if (n % 2) f *= {1 - n, 1};
  return f;
}

}  // namespace internal

// s(n,k) = [x^k]x(x-1)...(x-n+1)
template <class mint> std::vector<mint> stirling_first_kind(int n) {
  assert(0 <= n);
  return internal::stirling_first_kind_recursive<mint>(n);
}

}  // namespace cp