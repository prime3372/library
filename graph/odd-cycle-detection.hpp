#pragma once

#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

#include "graph/strongly-connected-components.hpp"

namespace cp {

template <bool directed> struct OddCycleDetection {
 public:
  OddCycleDetection() : n(0) {}
  explicit OddCycleDetection(int _n) : n(_n), g(_n), scc(_n) {}

  int add_edge(int from, int to) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    g[from].push_back(Edge{to, m});
    if (!directed) g[to].push_back(Edge{from, m});
    if (directed) scc.add_edge(from, to);
    return m++;
  }

  int len = -1;
  std::vector<int> vertices, edges;

  bool detect() {
    vertices.clear();
    edges.clear();
    if (directed) scc.build();
    std::vector<int> dist(2 * n, 2 * n);
    std::vector<int> prev_v(2 * n, -1);
    std::vector<int> prev_e(2 * n, -1);
    std::queue<int> que;
    for (int s = 0; s < n; s++) {
      if (dist[2 * s] < 2 * n || dist[2 * s + 1] < 2 * n) continue;
      dist[2 * s] = 0;
      que.emplace(2 * s);
      while (!que.empty()) {
        int x = que.front();
        que.pop();
        int v = x / 2, parity = x % 2;
        for (Edge& e : g[v]) {
          if (directed && scc.id[v] != scc.id[e.to]) continue;
          int y = 2 * e.to + !parity;
          if (dist[y] == 2 * n) {
            dist[y] = dist[x] + 1;
            prev_v[y] = x;
            prev_e[y] = e.id;
            que.push(y);
          }
        }
      }
      if (dist[2 * s + 1] == 2 * n) continue;

      for (int v = 2 * s + 1; v != 2 * s; v = prev_v[v]) {
        vertices.push_back(v / 2);
        edges.push_back(prev_e[v]);
      }
      vertices.push_back(s);
      std::reverse(vertices.begin(), vertices.end());
      std::reverse(edges.begin(), edges.end());

      std::vector<int> used(n, -1);
      int l = -1, r = -1;
      for (int i = 0; i < int(vertices.size()); i++) {
        if (used[vertices[i]] == -1) {
          used[vertices[i]] = i;
        } else {
          l = used[vertices[i]];
          r = i;
          break;
        }
      }
      len = r - l;
      vertices = std::vector(vertices.begin() + l, vertices.begin() + r);
      edges = std::vector(edges.begin() + l, edges.begin() + r);
      return true;
    }
    return false;
  }

 private:
  struct Edge {
    int to, id;
  };

  int n, m = 0;
  std::vector<std::vector<Edge>> g;
  StronglyConnectedComponents scc;
};

}  // namespace cp