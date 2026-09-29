#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

class odd_cycle_detection {
 public:
  odd_cycle_detection() : n(0) {}
  explicit odd_cycle_detection(int _n) : n(_n), g(_n) {}

  int add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(edge{v, m});
    g[v].push_back(edge{u, m});
    return m++;
  }

  int len = -1;
  std::vector<int> vertices, edges;

  bool detect() {
    vertices.clear();
    edges.clear();
    std::vector<bool> color(n), stacked(n), finished(n);
    auto dfs = [&](auto self, int v, int id) -> int {
      stacked[v] = true;
      for (auto e : g[v]) {
        if (e.id == id) continue;
        if (stacked[e.to]) {
          if (color[e.to] == color[v]) {
            vertices.push_back(v);
            edges.push_back(e.id);
            return e.to == v ? n : e.to;
          }
        } else if (!finished[e.to]) {
          color[e.to] = !color[v];
          int ret = self(self, e.to, e.id);
          if (ret == -1) continue;
          if (ret == n) return n;
          vertices.push_back(v);
          edges.push_back(e.id);
          return ret == v ? n : ret;
        }
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