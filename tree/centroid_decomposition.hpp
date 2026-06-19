#pragma once

#include <vector>

struct centroid_decomposition {
public:
  centroid_decomposition(int _n) : root(-1), tree(_n), sub(_n), removed(_n), n(_n), g(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int root;
  std::vector<std::vector<int>> tree;
  std::vector<int> sub;
  std::vector<bool> removed;

  centroid_decomposition& build(int s = 0) {
    assert(0 <= s && s < n);
    root = decomposite(s);
    return *this;
  }

private:
  int n;
  std::vector<std::vector<int>> g;

  int size(int v, int pv) {
    sub[v] = 1;
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      sub[v] += size(nv, v);
    }
    return sub[v];
  }

  int centroid(int v, int pv, int mid) {
    for (int nv : g[v]) {
      if (nv == pv || removed[nv]) continue;
      if (sub[nv] > mid) return centroid(nv, v, mid);
    }
    return v;
  }

  int decomposite(int v) {
    int cur = centroid(v, -1, size(v, -1) / 2);
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
