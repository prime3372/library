#pragma once

#include <cassert>
#include <queue>
#include <vector>

std::vector<int> topological_sort(const std::vector<std::vector<int>>& g) {
  int n = int(g.size());
  std::vector<int> in_deg(n);
  for (int u = 0; u < n; u++) {
    for (int v : g[u]) {
      assert(0 <= v && v < n);
      in_deg[v]++;
    }
  }
  std::queue<int> q;
  std::vector<int> res;
  for (int i = 0; i < n; ++i) {
    if (in_deg[i] == 0) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    res.push_back(u);
    for (int v : g[u]) {
      in_deg[v]--;
      if (in_deg[v] == 0) q.push(v);
    }
  }
  if (int(res.size()) != n) return {};
  return res;
}
