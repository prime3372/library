#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

struct doubling_lca {
public:
  doubling_lca() : doubling_lca(0) {}
  explicit doubling_lca(int _n) : n(_n), initialized(false), g(_n), dep(_n) {
    log = 1;
    while ((1 << log) < n) log++;
    par = std::vector<std::vector<int>>(log, std::vector<int>(n));
  }

  void add_edge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].push_back(b);
    g[b].push_back(a);
  }

  void init(int r = 0) {
    assert(0 <= r && r < n);
    dfs(r, r, 0);
    for (int i = 0; i < log - 1; i++) {
      for (int v = 0; v < n; v++) {
        par[i + 1][v] = par[i][par[i][v]];
      }
    }
    initialized = true;
  }

  int up(int v, int k) {
    assert(initialized);
    assert(0 <= v && v < n);
    for (int i = 0; k >> i; i++) {
      if ((k >> i) & 1) v = par[i][v];
    }
    return v;
  }

  int lca(int a, int b) {
    assert(initialized);
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    if (dep[a] > dep[b]) std::swap(a, b);
    b = up(b, dep[b] - dep[a]);
    if (a == b) return a;
    for (int i = log - 1; i >= 0; i--) {
      int na = par[i][a], nb = par[i][b];
      if (na != nb) {
        a = na;
        b = nb;
      }
    }
    return par[0][a];
  }

  int len(int a, int b) {
    int c = lca(a, b);
    return dep[a] + dep[b] - dep[c] * 2;
  }

  int jump(int s, int t, int k) {
    int l = len(s, t);
    if (l < k) return -1;
    return k < len(s, lca(s, t)) ? up(s, k) : up(t, l - k);
  }

  std::vector<int> path(int s, int t) const {
    assert(initialized);
    assert(0 <= s && s < n);
    assert(0 <= t && t < n);
    std::vector<int> pre, suf;
    while (dep[s] > dep[t]) {
      pre.push_back(s);
      s = par[0][s];
    }
    while (dep[s] < dep[t]) {
      suf.push_back(t);
      t = par[0][t];
    }
    while (s != t) {
      pre.push_back(s);
      suf.push_back(t);
      s = par[0][s];
      t = par[0][t];
    }
    pre.push_back(s);
    std::reverse(suf.begin(), suf.end());
    std::copy(suf.begin(), suf.end(), std::back_inserter(pre));
    return pre;
  }

private:
  int n, root, log;
  bool initialized;

  std::vector<std::vector<int>> g;
  std::vector<int> dep;

  std::vector<std::vector<int>> par;

  void dfs(int v, int pv, int d) {
    par[0][v] = pv;
    dep[v] = d;
    for (int nv : g[v]) {
      if (nv == pv) continue;
      dfs(nv, v, d + 1);
    }
  }
};
