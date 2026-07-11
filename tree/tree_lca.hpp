#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

#include "tree/hl_decomposition.hpp"

namespace cp {

struct tree_lca : private hl_decomposition {
public:
  tree_lca() : tree_lca(0) {}
  explicit tree_lca(int _n) : hl_decomposition(_n), dep(_n) {}

  using hl_decomposition::add_edge;

  void init(int r = 0) {
    assert(0 <= r && r < n);
    build(r);
    dfs(r, -1, 0);
    initialized = true;
  }

  int up(int v, int k) {
    assert(initialized);
    assert(0 <= v && v < n);
    v = id[v];
    while (k > v - head[v]) {
      k -= v - head[v] + 1;
      v = next[v];
    }
    return vertex[v - k];
  }

  int lca(int a, int b) {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = id[a];
    b = id[b];
    while (head[a] != head[b]) {
      if (a > b) std::swap(a, b);
      b = next[b];
    }    
    return vertex[std::min(a, b)];
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
  using hl_decomposition::id;
  using hl_decomposition::vertex;
  using hl_decomposition::head;
  using hl_decomposition::next;
  using hl_decomposition::n;
  using hl_decomposition::g;
  
  bool initialized = false;
  std::vector<int> dep;

  using hl_decomposition::build;

  void dfs(int v, int pv, int d) {
    dep[v] = d;
    for (int nv : g[v]) {
      if (nv == pv) continue;
      dfs(nv, v, d + 1);
    }
  }
};

} // namespace cp