#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <queue>
#include <tuple>

namespace cp {

template <class T> struct dijkstra {
public:
  dijkstra() : dijkstra(0) {}
  explicit dijkstra(int _n) : n(_n), g(_n), d(_n), prev_v(_n), prev_e(_n) {}

  int add_edge(int from, int to, T cost) {
    assert(0 <= from && to < n);
    assert(0 <= from && to < n);
    assert(0 <= cost);
    g[from].push_back(edge{to, m, cost});
    return m++;
  }  

  void search(int from) {
    assert(0 <= from && from < n);
    std::fill(d.begin(), d.end(), -1);
    using visit = std::tuple<T, int, int, int>;
    std::priority_queue<visit, std::vector<visit>, std::greater<visit>> q;
    q.emplace(0, from, from, -1);
    while (!q.empty()) {
      auto [c, v, pv, pe] = q.top();
      q.pop();
      if (d[v] != -1) continue;
      d[v] = c;
      prev_v[v] = pv;
      prev_e[v] = pe;
      for (auto e : g[v]) {
        q.emplace(c + e.cost, e.to, v, e.id);
      }
    }
  }

  T dist(int to) const {
    assert(0 <= to && to < n);
    return d[to];
  }

  std::pair<std::vector<int>, std::vector<int>> route(int to) const {
    assert(0 <= to && to < n);
    if (d[to] == -1) return {};
    std::vector<int> vs, es;
    while (to != prev_v[to]) {
      vs.push_back(to);
      es.push_back(prev_e[to]);
      to = prev_v[to];
    }
    vs.push_back(to);
    std::reverse(vs.begin(), vs.end());
    std::reverse(es.begin(), es.end());
    return {vs, es};
  }

private:
  int n, m = 0;
  struct edge {
    int to, id;
    T cost;
  };
  std::vector<std::vector<edge>> g;
  std::vector<T> d;
  std::vector<int> prev_v, prev_e;
};

} // namespace cp