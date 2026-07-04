#pragma once

#include <vector>

namespace cp {

template <class Str> std::vector<int> z_algorithm(const Str& s) {
  int n = int(s.size());
  if (n == 0) return {};
  std::vector<int> z(n);
  // contract: s[j,...,j+z[j]] = s[0,...,z[j]]
  for (int i = 1, j = 0; i < n; i++) {
    if (j + z[j] >= i) z[i] = std::min(z[i - j], j + z[j] - i); // s[i,...,j+z[j]] = s[i-j,...,z[j]]
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (j + z[j] < i + z[i]) j = i; // s[i,...,i+z[i]] = s[0,...,z[i]]
  }
  z[0] = n;
  return z;
}

} // namespace cp