#pragma once

#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>

#include "util/type-traits.hpp"

namespace cp {

// Dinic's Algorithm
template <class Cap>
  requires(internal::is_integral_v<Cap>)
class MaxFlow {
 public:
  MaxFlow() : MaxFlow(0) {}
  explicit MaxFlow(int _n) : n(_n), g(_n) {}

  int add_edge(int from, int to, Cap cap = 1) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    assert(0 <= cap);
    int m = int(pos.size());
    pos.emplace_back(from, int(g[from].size()));
    int from_id = int(g[from].size());
    int to_id = int(g[to].size());
    if (from == to) to_id++;
    g[from].push_back(_Edge{to, to_id, cap});
    g[to].push_back(_Edge{from, from_id, 0});
    return m;
  }

  struct Edge {
    int from, to;
    Cap cap, flow;
  };

  Edge get_edge(int i) {
    int m = int(pos.size());
    assert(0 <= i && i < m);
    auto e = g[pos[i].first][pos[i].second];
    auto re = g[e.to][e.rev];
    return Edge{pos[i].first, e.to, e.cap + re.cap, re.cap};
  }
  std::vector<Edge> edges() {
    std::vector<Edge> res(pos.size());
    for (int i = 0; i < int(pos.size()); i++) {
      auto e = g[pos[i].first][pos[i].second];
      auto re = g[e.to][e.rev];
      res[i] = Edge{pos[i].first, e.to, e.cap + re.cap, re.cap};
    }
    return res;
  }

  Cap flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max()); }
  Cap flow(int s, int t, Cap flow_limit) {
    assert(0 <= s && s < n);
    assert(0 <= t && t < n);
    assert(s != t);

    std::vector<int> level(n), iter(n);

    // BFS to construct the level graph.
    auto bfs = [&]() {
      std::fill(level.begin(), level.end(), -1);
      level[s] = 0;
      std::queue<int> que;
      que.push(s);
      while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (auto& e : g[v]) {
          if (e.cap == 0 || level[e.to] != -1) continue;
          level[e.to] = level[v] + 1;
          if (e.to == t) return;
          que.push(e.to);
        }
      }
    };

    // DFS to push augment flow backward from t to s along the level graph.
    auto dfs = [&](auto self, int v, Cap up) {
      // base case: reached the source s.
      if (v == s) return up;

      Cap res = 0;
      // Current-edge optimization:
      // resume loop from the last visited Edge index.
      for (int& i = iter[v]; i < int(g[v].size()); i++) {
        auto& e = g[v][i];
        if (g[e.to][e.rev].cap == 0 || level[v] <= level[e.to]) continue;
        Cap d = self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));
        g[v][i].cap += d;
        g[e.to][e.rev].cap -= d;
        res += d;
        if (res == up) return res;
      }
      level[v] = n;
      return res;
    };

    Cap flow = 0;
    while (flow < flow_limit) {
      bfs();
      // If sink t is unreachable, no more augmenting paths exist.
      if (level[t] == -1) break;
      std::fill(iter.begin(), iter.end(), 0);
      Cap f = dfs(dfs, t, flow_limit - flow);
      if (!f) break;
      flow += f;
    }
    return flow;
  }

  std::vector<bool> min_cut(int s) {
    assert(0 <= s && s < n);
    std::vector<bool> visited(n);
    std::queue<int> que;
    que.push(s);
    while (!que.empty()) {
      int p = que.front();
      que.pop();
      visited[p] = true;
      for (auto e : g[p]) {
        if (e.cap && !visited[e.to]) {
          visited[e.to] = true;
          que.push(e.to);
        }
      }
    }
    return visited;
  }

 private:
  struct _Edge {
    int to, rev;
    Cap cap;
  };

  int n;
  std::vector<std::pair<int, int>> pos;
  std::vector<std::vector<_Edge>> g;
};

}  // namespace cp