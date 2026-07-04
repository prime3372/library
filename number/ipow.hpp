#pragma once

#include <cassert>
#include <concepts>
#include <type_traits>

namespace cp {

template <std::integral T>
constexpr std::common_type_t<T, long long> ipow(T x, int n) {
  assert(0 <= n);
  std::common_type_t<T, long long> r = 1, t = x;
  while (n) {
    if (n & 1) r *= t;
    t *= t;
    n >>= 1;
  }
  return r;
}

} // namespace cp