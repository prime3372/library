#pragma once

#include <algorithm>
#include <utility>
#include <vector>

namespace cp {

// https://cp-algorithms.com/string/suffix-array.html O(NlogN) approach
// note: index[] and rank[] are used instead of p[] and c[]
template <class Str> std::vector<int> suffix_array(const Str& s) {
  int n = int(s.size()) + 1;

  std::vector<int> rank(n);
  int rank_num;
  {
    Str t = s;
    std::sort(t.begin(), t.end());
    auto last = std::unique(t.begin(), t.end());
    for (int i = 0; i < n - 1; i++) {
      rank[i] = int(std::lower_bound(t.begin(), last, s[i]) - t.begin()) + 1;
    }
    rank[n - 1] = 0;
    rank_num = int(t.size());
  }

  std::vector<int> index(n), cnt(n, 0);
  for (int i = 0; i < n; i++) cnt[rank[i]]++;
  for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; i++) index[--cnt[rank[i]]] = i;

  std::vector<int> nindex(n), nrank(n);
  for (int step = 0; (1 << step) < n; step++) {
    int w = 1 << step;

    std::fill(cnt.begin(), cnt.begin() + rank_num, 0);
    for (int i = 0; i < n; i++) cnt[rank[i]]++;
    for (int i = 1; i < rank_num; i++) cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; i--) {
      int j = index[i] - w;
      if (j < 0) j += n;
      nindex[--cnt[rank[j]]] = j;
    }

    rank_num = 1;
    nrank[nindex[0]] = 0;
    for (int i = 1; i < n; i++) {
      std::pair<int, int> cur = {rank[nindex[i]], rank[(nindex[i] + w) % n]};
      std::pair<int, int> prev = {rank[nindex[i - 1]], rank[(nindex[i - 1] + w) % n]};
      if (cur != prev) rank_num++;
      nrank[nindex[i]] = rank_num - 1;
    }

    index.swap(nindex);
    rank.swap(nrank);
  }
  return index;
}

} // namespace cp