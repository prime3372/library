#pragma once

#include <cassert>
#include <queue>
#include <vector>

namespace cp {

std::vector<int> topological_sort(const std::vector<std::vector<int>>& g) {
  int n = int(g.size());
  std::vector<int> in_deg(n);
  for (int u = 0; u < n; u++) {
    for (int v : g[u]) {
      assert(0 <= v && v < n);
      in_deg[v]++;
    }
  }
  std::queue<int> que;
  std::vector<int> res;
  for (int i = 0; i < n; ++i) {
    if (in_deg[i] == 0) que.push(i);
  }
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    res.push_back(u);
    for (int v : g[u]) {
      in_deg[v]--;
      if (in_deg[v] == 0) que.push(v);
    }
  }
  if (int(res.size()) != n) return {};
  return res;
}

} // namespace cp