#pragma once

#include <algorithm>
#include <utility>
#include <vector>

// https://cp-algorithms.com/string/suffix-array.html O(NlogN) approach
template <class Str> std::vector<int> suffix_array(const Str& s) {
  int n = int(s.size()) + 1;
  std::vector<int> a(n);
  Str t = s;
  std::sort(t.begin(), t.end());
  auto last = std::unique(t.begin(), t.end());
  for (int i = 0; i < n - 1; i++) {
    a[i] = int(std::lower_bound(t.begin(), last, s[i]) - t.begin()) + 1;
  }
  a[n - 1] = 0;

  std::vector<int> index(n), rank(n), cnt(n, 0);
  for (int i = 0; i < n; i++) cnt[a[i]]++;  
  for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; i++) index[--cnt[a[i]]] = i;  

  int num_of_ranks = 1;
  rank[index[0]] = 0;
  for (int i = 1; i < n; i++) {
    if (a[index[i]] != a[index[i - 1]]) num_of_ranks++;
    rank[index[i]] = num_of_ranks - 1;
  }

  std::vector<int> nindex(n), nrank(n);
  for (int k = 0; (1 << k) < n; k++) {
    for (int i = 0; i < n; i++) {
      index[i] -= 1 << k;
      if (index[i] < 0) index[i] += n;
    }
    std::fill(cnt.begin(), cnt.begin() + num_of_ranks, 0);
    for (int i = 0; i < n; i++) {
      cnt[rank[index[i]]]++;
    }
    for (int i = 1; i < num_of_ranks; i++) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      nindex[--cnt[rank[index[i]]]] = index[i];    
    }

    num_of_ranks = 1;
    nrank[nindex[0]] = 0;
    for (int i = 1; i < n; i++) {
      std::pair<int, int> cur = {rank[nindex[i]], rank[(nindex[i] + (1 << k)) % n]};
      std::pair<int, int> prev = {rank[nindex[i - 1]], rank[(nindex[i - 1] + (1 << k)) % n]};
      if (cur != prev) num_of_ranks++;
      nrank[nindex[i]] = num_of_ranks - 1;
    }

    index.swap(nindex);
    rank.swap(nrank);
  }
  return index;
}
