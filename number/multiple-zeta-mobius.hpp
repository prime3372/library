#pragma once

#include <vector>

namespace cp {

template <class T> void multiple_zeta(std::vector<T>& a) {
  int n = int(a.size());
  std::vector<bool> sieve(n, true);
  for (int p = 2; p < n; p++) {
    if (sieve[p]) {
      for (int k = (n - 1) / p; k >= 1; k--) {
        sieve[k * p] = false;
        a[k] += a[k * p];
      }
    }
  }
}

template <class T> void multiple_mobius(std::vector<T>& a) {
  int n = int(a.size());
  std::vector<bool> sieve(n, true);
  for (int p = 2; p < n; p++) {
    if (sieve[p]) {
      for (int k = 1; k * p < n; k++) {
        sieve[k * p] = false;
        a[k] -= a[k * p];
      }
    }
  }
}

}  // namespace cp