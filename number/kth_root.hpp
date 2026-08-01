#pragma once

#include <cassert>
#include <cmath>

#include "util/type_traits.hpp"

namespace cp {

template <class T, class U>
constexpr T kth_root(T x, U k) {
  assert(0 <= x && 1 <= k);
  if (x <= 1 || k == 1) return x;
  if (64 <= k) return 1;
  auto check = [&](unsigned __int128 y) {
    unsigned __int128 z = 1;
    for (int e = k; e; e >>= 1) {
      if (e & 1) z *= y;
      y *= y;
    }
    return z <= (unsigned __int128)(x);
  };
  T y = T(std::pow(double(x), 1.0 / k));
  while (!check(y)) y--;
  while (check(y + 1)) y++;
  return y;
}

} // namespace cp