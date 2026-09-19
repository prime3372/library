#pragma once

#include <cassert>
#include <limits>
#include <vector>

namespace cp {

class centroid_decomposition {
 public:
  centroid_decomposition() : n(0) {}
  explicit centroid_decomposition(int _n)
      : parent(_n, -1), size(_n), n(_n), g(_n), removed(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  std::vector<int> parent, size, dfs_ord;

  centroid_decomposition& build(int s = 0) {
    assert(0 <= s && s < n);
    dfs(s, -1, n, -1);
    return *this;
  }

 private:
  int n;
  std::vector<std::vector<int>> g;
  std::vector<bool> removed;

  int dfs(int v, int pv, int sz, int par) {
    if (removed[v]) return 0;
    int res = 1;
    bool ok = true;
    for (int nv : g[v]) {
      if (nv == pv) continue;
      int t = dfs(nv, v, sz, par);
      if (t == -1) return -1;
      res += t;
      if (t > sz / 2) ok = false;
    }
    if (!ok || sz - res > sz / 2) return res;
    parent[v] = par;
    size[v] = sz;
    dfs_ord.push_back(v);
    removed[v] = true;
    for (auto nv : g[v]) {
      dfs(nv, v, dfs(nv, v, std::numeric_limits<int>::max(), v), v);
    }
    return -1;
  }
};

}  // namespace cp