#pragma once

#include <vector>

#include "string/suffix_array.hpp"

namespace cp {

// Kasai's algorithm
template <class Str> std::vector<int> lcp_array(const Str& s, const std::vector<int>& sa) {
  int n = int(s.size());
  std::vector<int> rank(n + 1);
  for (int i = 0; i <= n; i++) {
    rank[sa[i]] = i;
  }
  std::vector<int> lcp(n);
  int h = 0;
  for (int i = 0; i <= n; i++) {
    if (h > 0) h--;
    if (rank[i] == 0) continue;
    int j = sa[rank[i] - 1];
    while (j + h < n && i + h < n && s[j + h] == s[i + h]) h++;
    lcp[rank[i] - 1] = h;
  }
  return lcp;
}
template <class Str> std::vector<int> lcp_array(const Str& s) {
  return lcp_array(s, suffix_array(s));
}

} // namespace cp