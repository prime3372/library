#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

template <bool directed> class cycle_detection {
 public:
  cycle_detection() : n(0) {}
  explicit cycle_detection(int _n) : n(_n), g(_n) {}

  int add_edge(int from, int to) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    g[from].push_back(edge{to, m});
    if (!directed) g[to].push_back(edge{from, m});
    return m++;
  }

  int len = -1;
  std::vector<int> vertices, edges;

  bool detect() {
    vertices.clear();
    edges.clear();
    std::vector<bool> stacked(n), finished(n);
    auto dfs = [&](auto self, int v, int id) -> int {
      if (stacked[v]) return v;
      stacked[v] = true;
      for (auto e : g[v]) {
        if (finished[e.to] || e.id == id) continue;
        int ret = self(self, e.to, e.id);
        if (ret == -1) continue;
        if (ret == n) return n;
        vertices.push_back(v);
        edges.push_back(e.id);
        return ret == v ? n : ret;
      }
      stacked[v] = false;
      finished[v] = true;
      return -1;
    };
    for (int v = 0; v < n; v++) {
      if (!finished[v] && dfs(dfs, v, -1) == n) break;
    }
    std::reverse(vertices.begin(), vertices.end());
    std::reverse(edges.begin(), edges.end());
    len = int(vertices.size());
    return len != 0;
  }

 private:
  int n, m = 0;
  struct edge {
    int to, id;
  };
  std::vector<std::vector<edge>> g;
};

}  // namespace cp