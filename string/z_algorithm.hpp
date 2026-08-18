#pragma once

#include <vector>

namespace cp {

template <class Str> std::vector<int> z_algorithm(const Str& s) {
  int n = int(s.size());
  if (n == 0) return {};
  std::vector<int> z(n);
  for (int i = 1, j = 0; i < n; i++) {
    // let s[l, r) denotes s[l,l+1,...,r-1], then
    // [1] s[j, j+z[j]) = s[0, z[j])
    // [2] s[i-j, i-j+z[i-j]) = s[0, z[i-j])

    if (i < j + z[j]) z[i] = std::min(z[i - j], j + z[j] - i);
    // s[i, j+z[j]) = s[i-j, z[j])                ...by[1]
    //              = s[0, min(z[i-j], j+z[j]-i)) ...by[2]

    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (j + z[j] < i + z[i]) j = i;
  }
  z[0] = n;
  return z;
}

}  // namespace cp