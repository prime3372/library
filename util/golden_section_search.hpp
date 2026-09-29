#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>

namespace cp {

// `f` is called exactly `k + 2` times.
// @return pair(argmin, min)
template <class F, class T = std::invoke_result_t<F, long double>,
          class Compare = std::less<T>>
std::pair<long double, T> golden_section_search(F f, long double l,
                                                long double r, int k,
                                                Compare compare = Compare()) {
  assert(l <= r);
  long double inv_phi = (std::sqrt(5) - 1.0) * 0.5;
  long double inv_phi_2 = inv_phi * inv_phi;
  long double a = l, b = r;
  long double x1 = a + inv_phi_2 * (b - a);
  long double x2 = a + inv_phi * (b - a);
  T y1 = f(x1), y2 = f(x2);
  for (int i = 0; i < k; i++) {
    if (compare(y1, y2)) {
      b = x2;
      x2 = x1;
      y2 = y1;
      x1 = a + inv_phi_2 * (b - a);
      y1 = f(x1);
    } else {
      a = x1;
      x1 = x2;
      y1 = y2;
      x2 = a + inv_phi * (b - a);
      y2 = f(x2);
    }
  }
  return compare(y1, y2) ? std::pair{x1, y1} : std::pair{x2, y2};
}

}  // namespace cp