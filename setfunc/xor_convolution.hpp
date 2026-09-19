#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

// @param n `|a| = |b| = 2**n`
// @note The mod must be an odd number.
template <class T>
std::vector<T> xor_convolution(int n, std::vector<T> a, std::vector<T> b) {
  assert(int(a.size()) == (1 << n));
  assert(int(b.size()) == (1 << n));

  for (int k = n; k >= 1; k--) {
    int width = 1 << k;
    int half = width / 2;
    for (int i = 0; i < (1 << n); i += width) {
      for (int j = 0; j < half; j++) {
        T l = a[i + j];
        T r = a[i + j + half];
        a[i + j] = l + r;
        a[i + j + half] = l - r;
      }
    }
  }

  for (int k = n; k >= 1; k--) {
    int width = 1 << k;
    int half = width / 2;
    for (int i = 0; i < (1 << n); i += width) {
      for (int j = 0; j < half; j++) {
        T l = b[i + j];
        T r = b[i + j + half];
        b[i + j] = l + r;
        b[i + j + half] = l - r;
      }
    }
  }

  for (int i = 0; i < (1 << n); i++) a[i] *= b[i];

  if constexpr (internal::is_modint_v<T>) {
    T inv2 = T(2).inv();
    for (int k = 1; k <= n; k++) {
      int width = 1 << k;
      int half = width / 2;
      for (int i = 0; i < (1 << n); i += width) {
        for (int j = 0; j < half; j++) {
          T l = a[i + j];
          T r = a[i + j + half];
          a[i + j] = (l + r) * inv2;
          a[i + j + half] = (l - r) * inv2;
        }
      }
    }
  } else {
    for (int k = 1; k <= n; k++) {
      int width = 1 << k;
      int half = width / 2;
      for (int i = 0; i < (1 << n); i += width) {
        for (int j = 0; j < half; j++) {
          T l = a[i + j];
          T r = a[i + j + half];
          a[i + j] = (l + r) / 2;
          a[i + j + half] = (l - r) / 2;
        }
      }
    }
  }

  return a;
}

}  // namespace cp