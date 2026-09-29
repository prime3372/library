#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>

namespace cp {

// `f` is called exactly `k + 2` times.
// @return pair(argmin, min)
template <class F, class Real, class T = std::invoke_result_t<F, Real>,
          class Compare = std::less<T>>
std::pair<Real, T> golden_section_search(F f, Real l, Real r, int k,
                                         Compare compare = Compare()) {
  assert(l <= r);
  Real inv_phi = (std::sqrt(5) - 1.0) * 0.5;
  Real inv_phi_2 = inv_phi * inv_phi;
  Real a = l, b = r;
  Real x1 = a + inv_phi_2 * (b - a);
  Real x2 = a + inv_phi * (b - a);
  Real y1 = f(x1), y2 = f(x2);
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
  return compare(y1, y2) ? std::pair<Real, Real>{x1, y1}
                         : std::pair<Real, Real>{x2, y2};
}

}  // namespace cp