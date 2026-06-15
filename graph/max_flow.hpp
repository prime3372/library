#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>
#include <queue>
#include <vector>

template <std::integral Cap> struct max_flow {
public:
  max_flow() : n(0) {}
  explicit max_flow(int _n) : n(_n), g(_n) {}

  int add_edge(int from, int to) { return add_edge(from, to, 1); }
  int add_edge(int from, int to, Cap cap) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    assert(0 <= cap);
    int m = int(pos.size());
    int from_id = int(g[from].size());
    int to_id = int(g[to].size());
    if (from == to) to_id++;
    pos.emplace_back(from, from_id);
    g[from].push_back(_edge{to, to_id, cap});
    g[to].push_back(_edge{from, from_id, 0});
    return m;
  }

  struct edge {
    int from, to;
    Cap cap, flow;
  };

  edge get_edge(int i) {
    int m = int(pos.size());
    assert(0 <= i && i < m);
    auto e = g[pos[i].first][pos[i].second];
    auto re = g[e.to][e.rev];
    return edge{pos[i].first, e.to, e.cap + re.cap, re.cap};
  }
  std::vector<edge> edges() {
    std::vector<edge> edges(pos.size());
    for (int i = 0; i < int(pos.size()); i++) {
      auto e = g[pos[i].first][pos[i].second];
      auto re = g[e.to][e.rev];
      edges[i] = edge{pos[i].first, e.to, e.cap + re.cap, re.cap};
    }
    return edges;
  }
  void change_edge(int i, Cap new_cap, Cap new_flow) {
      int m = int(pos.size());
      assert(0 <= i && i < m);
      assert(0 <= new_flow && new_flow <= new_cap);
      auto& e = g[pos[i].first][pos[i].second];
      auto& re = g[e.to][e.rev];
      e.cap = new_cap - new_flow;
      re.cap = new_flow;
  }

  Cap flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max()); }
  Cap flow(int s, int t, Cap flow_limit) {
    assert(0 <= s && s < n);
    assert(0 <= t && t < n);
    assert(s != t);

    std::vector<int> level(n), iter(n);
    std::queue<int> q;

    auto bfs = [&]() {
      std::fill(level.begin(), level.end(), -1);
      level[s] = 0;
      while (!q.empty()) q.pop();
      q.push(s);
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto e : g[v]) {
          if (e.cap == 0 || level[e.to] != -1) continue;
          level[e.to] = level[v] + 1;
          if (e.to == t) return;
          q.push(e.to);
        }
      }
    };

    auto dfs = [&](auto self, int v, Cap up) {
      if (v == s) return up;
      Cap res = 0;
      for (int& i = iter[v]; i < int(g[v].size()); i++) {
        auto e = g[v][i];
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
      if (level[t] == -1) break;
      std::fill(iter.begin(), iter.end(), 0);
      flow += dfs(dfs, t, flow_limit - flow);
    }
    return flow;
  }

  std::vector<bool> min_cut(int s) {
    std::vector<bool> visited(n);
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto e : g[v]) {
        if (e.cap && !visited[e.to]) {
          q.push(e.to);
          visited[e.to] = true;
        }
      }
    }
    return visited;
  }

private:
  int n;
  struct _edge {
    int to, rev;
    Cap cap;
  };
  std::vector<std::pair<int, int>> pos;
  std::vector<std::vector<_edge>> g;
};
