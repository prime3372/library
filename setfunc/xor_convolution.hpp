#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

// @param n `|a| = |b| = 2^n`
// @note The modulus must be an odd number.
template <class mint> requires internal::is_modint_v<mint>
std::vector<mint> xor_convolution(int n, std::vector<mint> a,
                                  std::vector<mint> b) {
  assert(int(a.size()) == (1 << n));
  assert(int(b.size()) == (1 << n));

  for (int k = n; k >= 1; k--) {
    int width = 1 << k;
    int half = width / 2;
    for (int i = 0; i < (1 << n); i += width) {
      for (int j = 0; j < half; j++) {
        mint l = a[i + j];
        mint r = a[i + j + half];
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
        mint l = b[i + j];
        mint r = b[i + j + half];
        b[i + j] = l + r;
        b[i + j + half] = l - r;
      }
    }
  }

  for (int i = 0; i < (1 << n); i++) a[i] *= b[i];

  mint inv2 = mint(2).inv();
  for (int k = 1; k <= n; k++) {
    int width = 1 << k;
    int half = width / 2;
    for (int i = 0; i < (1 << n); i += width) {
      for (int j = 0; j < half; j++) {
        mint l = a[i + j];
        mint r = a[i + j + half];
        a[i + j] = (l + r) * inv2;
        a[i + j + half] = (l - r) * inv2;
      }
    }
  }

  return a;
}

}  // namespace cp