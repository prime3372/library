#pragma once

#include <vector>

struct centroid_decomposition {
public:
  explicit centroid_decomposition(int _n) : root(-1), tree(_n), size(_n), removed(_n), n(_n), g(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int root;
  std::vector<std::vector<int>> tree;
  std::vector<int> size;
  std::vector<bool> removed;

  centroid_decomposition& build(int s = 0) {
    assert(0 <= s && s < n);
    root = decomposite(s);
    return *this;
  }

private:
  int n;
  std::vector<std::vector<int>> g;

  int calc_size(int v, int pv) {
    size[v] = 1;
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      size[v] += calc_size(nv, v);
    }
    return size[v];
  }

  int find_centroid(int v, int pv, int mid) {
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      if (size[nv] > mid) return find_centroid(nv, v, mid);
    }
    return v;
  }

  int decomposite(int v) {
    int cur = find_centroid(v, -1, calc_size(v, -1) / 2);
    removed[cur] = true;
    for (int to : g[cur]) {
      if (!removed[to]) {
        int nxt = decomposite(to);
        tree[cur].push_back(nxt);
      }
    }
    removed[cur] = false;
    return cur;
  }
};
