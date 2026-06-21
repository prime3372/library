#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>
#include "hl_decomposition.hpp"

#include <iostream>

struct tree_lca {
public:
  tree_lca() : tree_lca(0) {}
  explicit tree_lca(int _n) : n(_n), g(_n), dep(_n), hld(_n) {}

  void add_edge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].push_back(b);
    g[b].push_back(a);
    hld.add_edge(a, b);
  }

  void init(int r = 0) {
    assert(0 <= r && r < n);
    hld.build(r);
    dfs(r, r, 0);
    initialized = true;
  }

  int up(int v, int k) {
    assert(initialized);
    assert(0 <= v && v < n);
    int id = hld.id[v];
    while (k > id - hld.head[id]) {
      k -= id - hld.head[id] + 1;
      if (id == hld.next[id]) return hld.vertex[id];
      id = hld.next[id];
    }
    return hld.vertex[id - k];
  }

  int lca(int a, int b) {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = hld.id[a];
    b = hld.id[b];
    while (hld.head[a] != hld.head[b]) {
      if (a > b) std::swap(a, b);
      b = hld.next[b];
    }    
    return hld.vertex[std::min(a, b)];
  }

  int dist(int a, int b) {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    int c = lca(a, b);
    return dep[a] + dep[b] - dep[c] * 2;
  }

  int jump(int s, int t, int k) {
    assert(initialized);
    assert(0 <= s && s < n);
    assert(0 <= t && t < n);
    int l = dist(s, t);
    if (l < k) return -1;
    return k < dist(s, lca(s, t)) ? up(s, k) : up(t, l - k);
  }

private:
  int n;
  bool initialized = false;
  std::vector<std::vector<int>> g;
  std::vector<int> dep;
  hl_decomposition hld;

  void dfs(int v, int pv, int d) {
    dep[v] = d;
    for (int nv : g[v]) {
      if (nv == pv) continue;
      dfs(nv, v, d + 1);
    }
  }
};
