#pragma once

#include <cassert>
#include <cmath>

#include "util/math_utility.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> requires internal::is_integral_v<T>
constexpr T kth_root(T x, long long k) {
  assert(0 <= x && 1 <= k);
  if (x <= 1 || k == 1) return x;
  if (k == 2) return isqrt(x);
  if (k == 3) return icbrt(x);

  auto is_small_enough = [&](T y) {
    if (y == 0) return true;
    T z = 1;
    for (int e = k; e; e >>= 1) {
      if (e & 1) z *= y;      
      if (e > 1) {
        if (z > x / y / y) return false;
        y *= y;
      }
    }
    return z <= x;
  };

  T y = T(std::pow(double(x), 1.0 / k));
  while (!is_small_enough(y)) y--;
  while (is_small_enough(y + 1)) y++;
  return y;
}

} // namespace cp