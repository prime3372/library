#pragma once

#include <vector>

namespace cp {

template <class Str> std::vector<int> z_algorithm(const Str& s) {
  int n = int(s.size());
  if (n == 0) return {};
  std::vector<int> z(n);
  for (int i = 1, j = 0; i < n; i++) {
    // Assume:
    // [1] j < i
    // [2] s[k : k+z[k]] = s[0 : z[k]] (1 <= k < i)
    // When i < j+z[j] holds,
    // s[i : j+z[j]] = s[i-j : z[j]]
    //               = s[0 : min(z[i-j],j+z[j]-i)]
    if (i < j + z[j]) z[i] = std::min(z[i - j], j + z[j] - i);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (j + z[j] < i + z[i]) j = i;
  }
  z[0] = n;
  return z;
}

}  // namespace cp