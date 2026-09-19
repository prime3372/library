#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>

#include "util/type_traits.hpp"

namespace cp {

// [l, r]
template <bool get_min = true, class F,
          class T = std::invoke_result_t<F, long long>>
std::pair<long long, T> golden_section_search(F f, long long l, long long r) {
  assert(l <= r);
  long long a = l - 1, s = 1, t = 2;
  while (t < r - l + 2) std::swap(s += t, t);
  long long x = a + t - s, b = a + t;
  T fx = f(x), fy;
  while (a + b != 2 * x) {
    long long y = a + b - x;
    if (r < y || (fy = f(y), get_min ? fx < fy : fx > fy)) {
      b = a;
      a = y;
    } else {
      a = x;
      x = y;
      fx = fy;
    }
  }
  return {x, fx};
}

}  // namespace cp