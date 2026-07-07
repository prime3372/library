#pragma once

#include <cassert>
#include <vector>

namespace cp {

struct centroid_decomposition {
public:
  centroid_decomposition() : centroid_decomposition(0) {}
  explicit centroid_decomposition(int _n)
  : parent(_n, -1), size(_n, -1), depth(_n, -1), tree(_n), n(_n), g(_n), removed(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int root = -1;
  std::vector<int> parent, size, depth;
  std::vector<std::vector<int>> tree;
  std::vector<std::vector<std::vector<int>>> subtrees;

  centroid_decomposition& build(int s = 0) {
    assert(0 <= s && s < n);
    root = build(s, 0);
    parent[root] = -1;
    return *this;
  }

private:
  int n;
  std::vector<std::vector<int>> g;
  std::vector<bool> removed;

  void calc_size(int v, int pv) {
    size[v] = 1;
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      calc_size(nv, v);
      size[v] += size[nv];
    }
  }

  int find_centroid(int v, int pv, int mid) {
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      if (size[nv] > mid) {
        return find_centroid(nv, v, mid);
      }
    }
    return v;
  }

  void construct(int v, int pv, int dep, int c) {
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      subtrees[dep][v].push_back(nv);
      construct(nv, v, dep, c);
    }
  }

  int build(int v, int dep) {
    calc_size(v, -1);
    int c = find_centroid(v, -1, size[v] / 2);
    size[c] = size[v];
    depth[c] = dep;
    if (int(subtrees.size()) == dep) {
      subtrees.emplace_back(n);
    }
    construct(c, -1, dep, c);
    removed[c] = true;
    for (int to : g[c]) {
      if (removed[to]) continue;
      int nc = build(to, dep + 1);
      parent[nc] = c;
      tree[c].push_back(nc);
    }
    removed[c] = false;
    return c;
  }
};

} // namespace cp