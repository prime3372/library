#pragma once

#include <cassert>
#include <vector>

#include "graph/low-link.hpp"

namespace cp {

class TwoEdgeConnectedComponents {
 public:
  TwoEdgeConnectedComponents() : n(0) {}
  explicit TwoEdgeConnectedComponents(int _n) : n(_n), g(_n), link(_n) {}

  void add_edge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].push_back(b);
    g[b].push_back(a);
    link.add_edge(a, b);
  }

  int group_num = -1;
  std::vector<int> id;
  std::vector<std::vector<int>> groups;

  void build() {
    group_num = 0;
    id.assign(n, -1);
    link.build();
    auto dfs = [&](auto self, int v) -> void {
      id[v] = group_num;
      for (int nv : g[v]) {
        bool is_bridge = link.ord[v] < link.ord[nv]
                             ? link.ord[v] < link.low[nv]
                             : link.ord[nv] < link.low[v];
        if (id[nv] == -1 && !is_bridge) self(self, nv);
      }
    };
    for (int i = 0; i < n; i++) {
      if (id[i] == -1) {
        dfs(dfs, i);
        group_num++;
      }
    }
    groups.assign(group_num, std::vector<int>{});
    for (int i = 0; i < n; i++) groups[id[i]].push_back(i);
  }

 private:
  int n;
  std::vector<std::vector<int>> g;
  LowLink link;
};

}  // namespace cp