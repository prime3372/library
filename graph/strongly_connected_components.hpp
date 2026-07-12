#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

// Tarjan's strongly connected components algorithm
struct strongly_connected_components {
public:
  strongly_connected_components() : strongly_connected_components(0) {}
  explicit strongly_connected_components(int _n) : id(_n, -1), n(_n), g(_n) {}

  void add_edge(int from, int to) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    g[from].push_back(to);
  }

  std::vector<int> id;
  std::vector<std::vector<int>> scc;

  strongly_connected_components& build() {
    int now_ord = 0, group_num = 0;
    std::vector<int> visited, low(n), ord(n, -1);
    visited.reserve(n);

    auto dfs = [&](auto self, int v) -> void {
      low[v] = ord[v] = now_ord++;
      visited.push_back(v);
      for (int to : g[v]) {
        if (ord[to] == -1) {
          self(self, to);
          low[v] = std::min(low[v], low[to]);
        } else {
          low[v] = std::min(low[v], ord[to]);
        }
      }
      if (low[v] == ord[v]) {
        while (true) {
          int u = visited.back();
          visited.pop_back();
          ord[u] = n;
          id[u] = group_num;
          if (u == v) break;
        }
        group_num++;
      }
    };
    for (int i = 0; i < n; i++) {
      if (ord[i] == -1) dfs(dfs, i);
    }

    for (int& x : id) {
      x = group_num - 1 - x;
    }

    std::vector<int> counts(group_num);
    for (int x : id) counts[x]++;
    scc.resize(group_num);
    for (int i = 0; i < group_num; i++) {
      scc[i].reserve(counts[i]);
    }
    for (int i = 0; i < n; i++) {
      scc[id[i]].push_back(i);
    }

    return *this;
  }

private:
  int n;
  std::vector<std::vector<int>> g;
};

} // namespace cp