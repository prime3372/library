#pragma once

#include <vector>

#include "graph/low_link.hpp"

namespace cp {

struct two_edge_connected_components : private low_link {
public:
  two_edge_connected_components(int _n) : low_link(_n), id(_n, -1) {}

  using low_link::add_edge;

  std::vector<int> id;
  std::vector<std::vector<int>> groups;

  two_edge_connected_components& build() {
    low_link::build();

    int group_num = 0;
    auto dfs = [&](auto self, int v, int pv, int& k) -> void {
      if (pv != -1 && ord[pv] >= low[v]) {
        id[v] = id[pv];
      } else {
        id[v] = k++;
      }
      for (auto& e : g[v]) {
        if (id[e.to] == -1) self(self, e.to, v, k);        
      }
    };
    for (int i = 0; i < n; i++) {
      if (id[i] == -1) dfs(dfs, i, -1, group_num);      
    }

    std::vector<int> counts(group_num);
    for (int x : id) counts[x]++;
    groups.resize(group_num);
    for (int i = 0; i < group_num; i++) {
      groups[i].reserve(counts[i]);
    }
    for (int i = 0; i < n; i++) {
      groups[id[i]].push_back(i);
    }
 
    return *this;
  }

private:
  using low_link::ord;
  using low_link::low;
  using low_link::n;
  using low_link::g;
};

} // namespace cp