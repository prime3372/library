#pragma once

#include <cassert>
#include <vector>

#include "graph/low_link.hpp"

namespace cp {

class two_edge_connected_components {
 public:
  two_edge_connected_components() : n(0) {}
  explicit two_edge_connected_components(int _n)
      : id(_n), n(_n), g(_n), link(_n) {}

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

  two_edge_connected_components& build() {
    group_num = 0;
    std::fill(id.begin(), id.end(), -1);
    link.build();
    auto dfs = [&](auto self, int v) -> void {
      id[v] = group_num;
      for (int nv : g[v]) {
        bool bridge = link.ord[v] < link.ord[nv] ? link.ord[v] < link.low[nv]
                                                 : link.ord[nv] < link.low[v];
        if (id[nv] == -1 && !bridge) self(self, nv);
      }
    };
    for (int i = 0; i < n; i++) {
      if (id[i] == -1) {
        dfs(dfs, i);
        group_num++;
      }
    }
    groups.assign(group_num, {});
    for (int i = 0; i < n; i++) groups[id[i]].push_back(i);
    return *this;
  }

 private:
  int n;
  std::vector<std::vector<int>> g;
  low_link link;
};

}  // namespace cp