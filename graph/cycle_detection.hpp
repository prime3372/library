#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

template <bool is_directed> struct cycle_detection {
public:  
  cycle_detection() : cycle_detection(0) {}
  explicit cycle_detection(int _n) : n(_n), g(_n) {}

  int add_edge(int from, int to) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    g[from].push_back(edge{to, m});
    if constexpr (!is_directed) g[to].push_back(edge{from, m});
    return m++;
  }

  int len = 0;
  std::vector<int> vertices, edges;

  cycle_detection& detect() {
    vertices.clear();
    edges.clear();
    std::vector<int> visited(n);
    auto dfs = [&](this auto& self, int v, int id) -> int {
      if (visited[v] == 1) return v;
      visited[v] = 1;
      for (auto e : g[v]) {
        if (visited[e.to] == -1 || e.id == id) continue;
        int ret = self(e.to, e.id);
        if (ret == -1) continue;
        if (ret == n) return n;
        vertices.push_back(v);
        edges.push_back(e.id);
        return ret == v ? n : ret;
      }
      visited[v] = -1;
      return -1;
    };
    for (int v = 0; v < n; v++) {
      if (!visited[v] && dfs(v, -1) == n) break;
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
