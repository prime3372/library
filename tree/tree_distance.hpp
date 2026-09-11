#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "tree/hl_decomposition.hpp"

namespace cp {

template <class T> class tree_distance {
 public:
  tree_distance() : n(0) {}
  explicit tree_distance(int _n) : n(_n), g(_n), cost(_n), hld(_n) {}

  void add_edge(int a, int b, T c) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].emplace_back(b, c);
    g[b].emplace_back(a, c);
    hld.add_edge(a, b);
  }

  void init(int r = 0) {
    assert(0 <= r && r < n);
    hld.build(r);
    dfs(r, -1, 0);
    initialized = true;
  }

  int operator()(int a, int b) {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = hld.ord[a];
    b = hld.ord[b];
    while (hld.head[a] != hld.head[b]) {
      if (a > b) std::swap(a, b);
      b = hld.next[b];
    }
    int l = hld.vertex[std::min(a, b)];
    return cost[a] + cost[b] - cost[l] * 2;
  }

 private:
  int n;
  bool initialized = false;
  std::vector<std::vector<std::pair<int, T>>> g;
  std::vector<T> cost;
  hl_decomposition hld;

  void dfs(int v, int pv, T c) {
    cost[v] = c;
    for (auto [nv, x] : g[v]) {
      if (nv != pv) dfs(nv, v, c + x);
    }
  }
};

}  // namespace cp