#pragma once

#include <cassert>
#include <vector>

namespace cp {

struct centroid_decomposition {
public:
  centroid_decomposition() : n(0) {}
  explicit centroid_decomposition(int _n) : parent(_n, -1), size(_n), tree(_n),
                                            n(_n), g(_n), removed(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int root = -1;
  std::vector<int> centroid, parent, size;
  std::vector<std::vector<int>> tree; // directed

  centroid_decomposition& build() {
    centroid.reserve(n);
    root = build(0);
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

  int build(int v) {
    calc_size(v, -1);
    int c = find_centroid(v, -1, size[v] / 2);
    centroid.push_back(c);
    size[c] = size[v];
    removed[c] = true;
    for (int to : g[c]) {
      if (removed[to]) continue;
      int nc = build(to);
      parent[nc] = c;
      tree[c].push_back(nc);
    }
    return c;
  }
};

} // namespace cp