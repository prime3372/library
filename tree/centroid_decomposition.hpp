#pragma once

#include <cassert>
#include <vector>

namespace cp {

class centroid_decomposition {
 public:
  centroid_decomposition() : n(0) {}
  explicit centroid_decomposition(int _n)
      : parent(_n, -1), size(_n), n(_n), g(_n), removed(_n), tmp_size(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  std::vector<int> parent, size, dfs_order;

  int build(int v = 0) {
    calc_size(v, -1);
    int c = find_centroid(v, -1, tmp_size[v] / 2);
    dfs_order.push_back(c);
    size[c] = tmp_size[v];
    removed[c] = true;
    for (int to : g[c]) {
      if (removed[to]) continue;
      parent[build(to)] = c;
    }
    return c;
  }

 private:
  int n;
  std::vector<std::vector<int>> g;
  std::vector<bool> removed;
  std::vector<int> tmp_size;

  void calc_size(int v, int pv) {
    tmp_size[v] = 1;
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      calc_size(nv, v);
      tmp_size[v] += tmp_size[nv];
    }
  }

  int find_centroid(int v, int pv, int mid) {
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      if (tmp_size[nv] > mid) return find_centroid(nv, v, mid);
    }
    return v;
  }
};

}  // namespace cp