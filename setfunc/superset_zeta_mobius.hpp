#pragma once

#include <cassert>
#include <vector>

namespace cp {

// superset zeta transform
template <class T> void superset_zeta(int n, std::vector<T>& a) {
  assert(0 <= n && int(a.size()) == (1 << n));
  // example: n = 8
  // [000] -> [00*] -> [0**] -> [***]
  // [001] -> [001] -> [0*1] -> [**1]
  // [010] -> [01*] -> [01*] -> [*1*]
  // [011] -> [011] -> [011] -> [*11]
  // [100] -> [10*] -> [1**] -> [1**]
  // [101] -> [101] -> [1*1] -> [1*1]
  // [110] -> [11*] -> [11*] -> [11*]
  // [111] -> [111] -> [111] -> [111]
  for (int i = 0; i < n; i++) {
    int b = 1 << i;
    for (int l = 0; l < (1 << n); l += 2 * b) {
      for (int t = l; t < l + b; t++) {
        a[t] += a[t + b];
      }
    }
  }
}

// superset mobius transform
template <class T> void superset_mobius(int n, std::vector<T>& a) {
  assert(0 <= n && int(a.size()) == (1 << n));
  // example: n = 8
  // [***] -> [**0] -> [*00] -> [000]
  // [**1] -> [**1] -> [*01] -> [001]
  // [*1*] -> [*10] -> [*10] -> [010]
  // [*11] -> [*11] -> [*11] -> [011]
  // [1**] -> [1*0] -> [100] -> [100]
  // [1*1] -> [1*1] -> [101] -> [101]
  // [11*] -> [110] -> [110] -> [110]
  // [111] -> [111] -> [111] -> [111]
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