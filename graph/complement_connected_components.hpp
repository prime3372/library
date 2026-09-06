#pragma once

#include <vector>

#include "ds/union_find.hpp"

namespace cp {

class complement_connected_components {
 public:
  complement_connected_components() : n(0) {}
  complement_connected_components(int _n) : n(_n), g(_n) {}
  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  std::vector<std::vector<int>> calc() {
    if (n == 0) return {};
    int min_deg = int(g[0].size());
    int min_deg_v = 0;
    for (int i = 1; i < n; i++) {
      if (int(g[i].size()) < min_deg) {
        min_deg = int(g[i].size());
        min_deg_v = i;
      }
    }
    union_find uf(n);
    std::vector<bool> c(n);
    for (int i : g[min_deg_v]) c[i] = true;
    for (int i = 0; i < n; i++) {
      if (!c[i]) {
        uf.unite(min_deg_v, i);
        continue;
      }
      std::vector<bool> ci(n);
      for (int j : g[i]) ci[j] = true;
      for (int j = 0; j < n; j++) {
        if (!ci[j]) uf.unite(i, j);
      }
    }
    return uf.groups();
  }

 private:
  int n;
  std::vector<std::vector<int>> g;
};

}  // namespace cp