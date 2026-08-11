#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

template <bool is_directed> struct cycle_detection {
public:  
  cycle_detection() : n(0) {}
  explicit cycle_detection(int _n) : n(_n), g(_n) {}

  int add_edge(int from, int to) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    g[from].push_back(edge{to, m});
    if constexpr (!is_directed) {
      g[to].push_back(edge{from, m});
    }
    return m++;
  }

  int len = 0;
  std::vector<int> vertices, edges;

  cycle_detection& detect() {
    vertices.clear();
    edges.clear();
    std::vector<bool> processing(n), processed(n);
    auto dfs = [&](auto self, int v, int id) -> int {
      if (processing[v]) return v;
      processing[v] = true;
      int ret = -1;
      for (auto e : g[v]) {
        if (processed[e.to] == true || e.id == id) continue;
        ret = self(self, e.to, e.id);
        if (ret != -1) break;
      }
      processing[v] = false;
      processed[v] = true;
      if (ret == -1 || ret == n) return ret;
      vertices.push_back(v);
      edges.push_back(e.id);
      return ret == v ? n : ret;
    };
    for (int v = 0; v < n; v++) {
      if (!processed[v] && dfs(dfs, v, -1) == n) break;
    }
    std::reverse(vertices.begin(), vertices.end());
    std::reverse(edges.begin(), edges.end());
    len = int(vertices.size());
    return *this;
  }

private:
  int n, m = 0;
  struct edge {
    int to, id;
  };
  std::vector<std::vector<edge>> g;
};

} // namespace cp