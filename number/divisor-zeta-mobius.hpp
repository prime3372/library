#pragma once

#include <vector>

namespace cp {

// @note 0 is treated as a divisor of any integer.
template <class T> void divisor_zeta(std::vector<T>& a) {
  int n = int(a.size());
  std::vector<bool> sieve(n, true);
  for (int i = 1; i < n; i++) a[0] += a[i];
  for (int p = 2; p < n; p++) {
    if (sieve[p]) {
      for (int k = 1; k * p < n; k++) {
        sieve[k * p] = false;
        a[k * p] += a[k];
      }
    }
  }
}

// @note 0 is treated as a divisor of any integer.
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
  for (int i = 1; i < n; i++) a[0] -= a[i];
}

}  // namespace cp