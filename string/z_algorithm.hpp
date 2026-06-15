#pragma once

#include <vector>

template <class Str> std::vector<int> z_algorithm(const Str& s) {
  int n = int(s.size());
  if (n == 0) return {};
  std::vector<int> z(n);
  for (int i = 1, j = 0; i < n; i++) {
    if (j + z[j] >= i) z[i] = std::min(z[i - j], j + z[j] - i);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (j + z[j] < i + z[i]) j = i;
  }
  z[0] = n;
  return z;
}
