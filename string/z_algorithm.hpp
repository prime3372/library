#pragma once

#include <vector>

namespace cp {

template <class Str> std::vector<int> z_algorithm(const Str& s) {
  int n = int(s.size());
  if (n == 0) return {};
  std::vector<int> z(n);
  for (int i = 1, j = 0; i < n; i++) {
    // [1] j < i
    // [2] s[k : k+z[k]] = s[0 : z[k]] (k=0,1,...,i-1)
    // s[i : j+z[j]] = s[i-j : z[j]]               ...by[1][2]
    //               = s[0 : min(z[i-j],j+z[j]-i)] ...by[2]
    if (i < j + z[j]) z[i] = std::min(z[i - j], j + z[j] - i);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (j + z[j] - i < z[i]) j = i;
  }
  z[0] = n;
  return z;
}

}  // namespace cp