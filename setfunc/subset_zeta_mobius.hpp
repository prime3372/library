#pragma once

#include <cassert>
#include <vector>

namespace cp {

// subset zeta transfrom
template <class T> void subset_zeta(int n, std::vector<T>& a) {
  assert(0 <= n && int(a.size()) == (1 << n));
  // example: n = 8
  // [000] -> [000] -> [000] -> [000]
  // [001] -> [00*] -> [00*] -> [00*]
  // [010] -> [010] -> [0*0] -> [0*0]
  // [011] -> [01*] -> [0**] -> [0**]
  // [100] -> [100] -> [100] -> [*00]
  // [101] -> [10*] -> [10*] -> [*0*]
  // [110] -> [110] -> [1*0] -> [**0]
  // [111] -> [11*] -> [1**] -> [***]
  for (int i = 0; i < n; i++) {
    int b = 1 << i;
    for (int l = 0; l < (1 << n); l += 2 * b) {
      for (int t = l; t < l + b; t++) {
        a[t + b] += a[t];
      }
    }
  }
}

// subset mobius transform
template <class T> void subset_mobius(int n, std::vector<T>& a) {
  assert(0 <= n && int(a.size()) == (1 << n));
  // example: n = 8
  // [000] -> [000] -> [000] -> [000]
  // [00*] -> [001] -> [001] -> [001]
  // [0*0] -> [0*0] -> [010] -> [010]
  // [0**] -> [0*1] -> [011] -> [011]
  // [*00] -> [*00] -> [*00] -> [100]
  // [*0*] -> [*01] -> [*01] -> [101]
  // [**0] -> [**0] -> [*10] -> [110]
  // [***] -> [**1] -> [*11] -> [111]
  for (int i = 0; i < n; i++) {
    int b = 1 << i;
    for (int l = 0; l < (1 << n); l += 2 * b) {
      for (int t = l; t < l + b; t++) {
        a[t + b] -= a[t];
      }
    }
  }
}

}  // namespace cp