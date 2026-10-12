#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>

namespace cp {

// [l, r]
// @return pair(argmin, min)
template <class F, class T = std::invoke_result_t<F, long long>,
          class Compare = std::less<T>>
std::pair<long long, T> fibonacci_search(F f, long long l, long long r,
                                         Compare compare = Compare()) {
  assert(l <= r);
  long long s = 1, t = 2;
  while (t < r - l + 2) std::swap(s += t, t);
  long long a = l - 1, x1 = a + t - s, b = a + t;
  T y1 = f(x1), y2;
  while (a + b != x1 * 2) {
    long long x2 = a + b - x1;
    if (r < x2 || (y2 = f(x2), compare(y1, y2))) {
      b = a;
      a = x2;
    } else {
      a = x1;
      x1 = x2;
      y1 = y2;
    }
  }
  return {x1, y1};
}

}  // namespace cp