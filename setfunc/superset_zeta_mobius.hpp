#pragma once

#include <cassert>
#include <vector>

namespace cp {

template <class T> void superset_zeta(int n, std::vector<T>& a) {
  assert(0 <= n && int(a.size()) == 1 << n);
  for (int i = 0; i < n; i++) {
    int b = 1 << i;
    for (int l = 0; l < (1 << n); l += 2 * b) {
      for (int t = l; t < l + b; t++) {
        a[t] += a[t + b];
      }
    }
  }
}

template <class T> void superset_mobius(int n, std::vector<T>& a) {
  assert(0 <= n && int(a.size()) == 1 << n);
  for (int i = 0; i < n; i++) {
    int b = 1 << i;
    for (int l = 0; l < (1 << n); l += 2 * b) {
      for (int t = l; t < l + b; t++) {
        a[t] -= a[t + b];
      }
    }
  }
}

}  // namespace cp