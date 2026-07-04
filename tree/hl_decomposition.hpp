#pragma once

#include <utility>
#include <vector>

namespace cp {

struct hl_decomposition {
public:
  hl_decomposition() : hl_decomposition(0) {}
  explicit hl_decomposition(int _n)
  : id(_n, -1), vertex(_n, -1), head(_n, -1), next(_n, -1), n(_n), g(_n), size(_n) {}

  void add_edge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].push_back(b);
    g[b].push_back(a);
  }

  std::vector<int> id, vertex, head, next;

  hl_decomposition& build(int r = 0) {
    assert(0 <= r && r < n);

    auto first_dfs = [&](auto self, int v, int pv) -> void {
      size[v] = 1;
      if (!g[v].empty() && g[v][0] == pv) {
        std::swap(g[v][0], g[v].back());
      }
      for (int& nv : g[v]) {
        if (nv == pv) continue;
        self(self, nv, v);
        size[v] += size[nv];
        if (size[nv] > size[g[v][0]]) std::swap(g[v][0], nv);
      }
    };
    first_dfs(first_dfs, r, -1);

    auto second_dfs = [&](auto self, int v, int pv) -> void {
      id[v] = k;
      vertex[k++] = v;
      for (int nv : g[v]) {
        if (nv == pv) continue;
        head[k] = g[v][0] == nv ? head[id[v]] : k;
        next[k] = g[v][0] == nv ? next[id[v]] : id[v];
        self(self, nv, v);
      }
    };
    head[k] = k;
    next[k] = -1;
    second_dfs(second_dfs, r, -1);
    return *this;
  }

private:
  int n, k = 0;
  std::vector<std::vector<int>> g;
  std::vector<int> size;
};

} // namespace cp