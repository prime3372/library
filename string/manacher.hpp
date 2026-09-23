#pragma once

#include <string>
#include <vector>

namespace cp {

template <class Str> std::vector<int> manacher(const Str& s) {
  int n = int(s.size());
  Str t(2 * n + 1, -1);
  for (int i = 0; i < n; i++) t[2 * i + 1] = s[i];
  n = 2 * n + 1;
  std::vector<int> rad(n);
  int c = 0, r = 0;
  while (c < n) {
    while (0 <= c - r && c + r < n && t[c - r] == t[c + r]) r++;
    rad[c] = r;
    int k = 1;
    while (0 <= c - k && k + rad[c - k] < r) {
      rad[c + k] = rad[c - k];
      k++;
    }
    c += k;
    r -= k;
  }
  std::vector<int> ans(n - 2);
  for (int i = 0; i < n - 2; i++) ans[i] = rad[i + 1] - 1;
  return ans;
}

}  // namespace cp