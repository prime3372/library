#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>

namespace cp {

// [l, r]
template <class F, class T = std::invoke_result_t<F, long long>,
          class Compare = std::less<T>>
std::pair<long long, T> fibonacci_search(F f, long long l, long long r,
                                         Compare compare = Compare()) {
  assert(l <= r);
  long long s = 1, t = 2;
  while (t < r - l + 2) std::swap(s += t, t);
  long long a = l - 1, x = a + t - s, b = a + t;
  T fx = f(x), fy;
  while (a + b != 2 * x) {
    long long y = a + b - x;
    if (r < y || (fy = f(y), compare(fx, fy))) {
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