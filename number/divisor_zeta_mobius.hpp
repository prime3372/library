#pragma once

#include <vector>

namespace cp {

// @note The value of a[0] doesn't affect the transform at all.
template <class T> void divisor_zeta(std::vector<T>& a) {
  int n = int(a.size());
  std::vector<bool> sieve(n, true);
  for (int p = 2; p < n; p++) {
    if (sieve[p]) {
      for (int k = 1; k * p < n; k++) {
        sieve[k * p] = false;
        a[k * p] += a[k];
      }
    }
  }
}

// @note The value of a[0] doesn't affect the transform at all.
template <class T> void divisor_mobius(std::vector<T>& a) {
  int n = int(a.size());
  std::vector<bool> sieve(n, true);
  for (int p = 2; p < n; p++) {
    if (sieve[p]) {
      for (int k = (n - 1) / p; k >= 1; k--) {
        sieve[k * p] = false;
        a[k * p] -= a[k];
      }
    }
  }
}

}  // namespace cp