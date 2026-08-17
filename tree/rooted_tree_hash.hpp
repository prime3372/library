#pragma once

#include <algorithm>
#include <vector>

#include "util/hash61.hpp"

namespace cp {

struct rooted_tree_hash {
 public:
  rooted_tree_hash(int _n) : hash(_n), depth(_n), n(_n), g(_n) {
    while (int(xs.size()) <= n) {
      xs.push_back(hash61::get_rand());
    }
  }

  void add_edge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].push_back(b);
    g[b].push_back(a);
  }

  std::vector<hash61> hash;
  std::vector<int> depth;

  rooted_tree_hash& build(int r) {
    dfs(r, -1);
    return *this;
  }

 private:
  inline static std::vector<hash61> xs;
  int n;
  std::vector<std::vector<int>> g;

 int dfs(int v, int pv) {
    int dep = 0;
    for (int nv : g[v]) {
      if (nv != pv) dep = std::max(dep, dfs(nv, v) + 1);
    }
    hash61 x = xs[dep], h = 1;
    for (int nv : g[v]) {
      if (nv != pv) h = h * (x + hash[nv]);
    }
    hash[v] = h;
    return depth[v] = dep;
  }
};

} // namespace cp