#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "tree/lowest_common_ancestor.hpp"

namespace cp {

template <class T> class tree_distance {
 public:
  tree_distance() : n(0) {}
  explicit tree_distance(int _n) : n(_n), cost(_n), lca(_n) {}

  void add_edge(int a, int b, T c) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].emplace_back(b, c);
    g[b].emplace_back(a, c);
  }

  void init() {
    lca.init(0);
    dfs(0, -1, 0);
    initialized = true;
  }

  T operator()(int a, int b) {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    int l = lca(a, b);
    return cost[a] + cost[b] - cost[l] * 2;
  }

 private:
  int n;
  bool initialized = false;
  std::vector<std::vector<std::pair<int, T>>> g;
  std::vector<T> cost;
  lowest_common_ancestor lca;

  void dfs(int v, int pv, int c) {
    cost[v] = c;
    for (auto [nv, x] : g[v]) {
      if (nv == pv) continue;
      dfs(nv, v, c + x);
    }
  }
};

}  // namespace cp