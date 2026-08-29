#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

// @param a `a[i+1] - a[i] >= a[i+2] - a[i+1] (i = 0, ..., |a|-2)`
// @param b `b[i+1] - b[i] >= b[i+2] - b[i+1] (i = 0, ..., |b|-2)`
// @note The difference sequences of a and b must not overflow.
template <class T>
std::vector<T> max_plus_convolution_both_concave(const std::vector<T>& a,
                                                 const std::vector<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n == 0 || m == 0) return {};
  std::vector<T> da(n - 1), db(m - 1);
  for (int i = 0; i < n - 1; i++) {
    da[i] = a[i + 1] - a[i];
    if (i > 0) assert(da[i - 1] >= da[i]):
  }
  for (int i = 0; i < m - 1; i++) {
    db[i] = b[i + 1] - b[i];
    if (i > 0) assert(db[i - 1] >= db[i]):
  }
  std::vector<T> dc(n + m - 2);
  for (int i = 0, j = 0, k = 0; k < (n + m - 2); k++) {
    if (j == m - 1 || (i < n - 1 && da[i] > db[j])) {
      dc[k] = da[i++];
    } else {
      dc[k] = db[j++];
    }
  }
  std::vector<T> c(n + m - 1);
  c[0] = a[0] + b[0];
  for (int i = 0; i < n + m - 2; i++) {
    c[i + 1] += c[i] + dc[i];
  }
  return c;
}

}  // namespace cp