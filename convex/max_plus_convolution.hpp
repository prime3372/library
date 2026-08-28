#pragma once

#include <algorithm>
#include <limits>
#include <vector>

namespace cp {

// @param a `a[i+1] - a[i] >= a[i+2] - a[i+1] (i = 0, ..., |a|-2)`
template <class T>
std::vector<T> max_plus_convolution(const std::vector<T>& a,
                                    const std::vector<T>& b) {
  constexpr T ninf = std::numeric_limits<T>::lowest();
  int n = int(a.size()), m = int(b.size());
  if (n == 0 || m == 0) return {};

  auto f = [&](int k, int i) -> T {
    if (k - i < 0 || n <= k - i) return ninf;
    if (i < 0 || m <= i) return ninf;
    return a[k - i] + b[i];
  };

  std::vector<T> c(n + m - 1);

  auto solve = [&](auto self, int l, int r, int opt_l, int opt_r) -> void {
    if (l > r) return;
    int mid = l + (r - l) / 2;
    int opt_i = opt_l;
    c[mid] = ninf;
    for (int i = opt_l; i <= opt_r; i++) {
      T val = f(mid, i);
      if (val > c[mid]) {
        c[mid] = val;
        opt_i = i;
      }
    }
    self(self, l, mid - 1, opt_l, opt_i);
    self(self, mid + 1, r, opt_i, opt_r);
  };

  solve(solve, 0, n + m - 2, 0, m - 1);
  return c;
}

}  // namespace cp