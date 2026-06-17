#pragma once

#include "pow_mod.hpp"

constexpr int primitive_root_constexpr(int p) {
  if (p == 2) return 1;
  if (p == 167772161) return 3;
  if (p == 469762049) return 3;
  if (p == 754974721) return 11;
  if (p == 998244353) return 3;
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1;
  int x = (p - 1) / 2;
  while (x % 2 == 0) x /= 2;
  for (int i = 3; 1LL * i * i <= x; i += 2) {
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) {
    divs[cnt++] = x;
  }
  for (int g = 2;; g++) {
    bool ok = true;
    for (int i = 0; i < cnt; i++) {
      if (pow_mod(g, (p - 1) / divs[i], p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}
