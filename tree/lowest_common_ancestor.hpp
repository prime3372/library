#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "tree/hl_decomposition.hpp"

namespace cp {

class lowest_common_ancestor {
 public:
  lowest_common_ancestor() : n(0) {}
  explicit lowest_common_ancestor(int _n) : n(_n), g(_n), dep(_n), hld(_n) {}

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
    dfs(r, -1, 0);
    initialized = true;
  }

  int operator()(int a, int b) const {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = hld.ord[a];
    b = hld.ord[b];
    while (hld.head[a] != hld.head[b]) {
      if (a > b) std::swap(a, b);
      b = hld.next[b];
    }
    return hld.vertex[std::min(a, b)];
  }

  int dist(int a, int b) const {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    int c = (*this)(a, b);
    return dep[a] + dep[b] - dep[c] * 2;
  }

  int up(int v, int k) const {
    assert(initialized);
    assert(0 <= v && v < n);
    v = hld.ord[v];
    while (k > v - hld.head[v]) {
      k -= v - hld.head[v] + 1;
      v = hld.next[v];
    }
    return hld.vertex[v - k];
  }

  int jump(int s, int t, int k) const {
    assert(initialized);
    assert(0 <= s && s < n);
    assert(0 <= t && t < n);
    int l = dist(s, t);
    if (l < k) return -1;
    return k < dist(s, (*this)(s, t)) ? up(s, k) : up(t, l - k);
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

}  // namespace cp