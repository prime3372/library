#pragma once

#include <utility>
#include <vector>

struct hl_decomposition {
public:
  hl_decomposition() : hl_decomposition(0) {}
  explicit hl_decomposition(int _n) : n(_n), g(_n) {}

  void add_edge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].push_back(b);
    g[b].push_back(a);
  }

  std::vector<int> id, vertex, head, next, size;

  hl_decomposition& build(int r = 0) {
    assert(0 <= r && r < n);
    id = vertex = head = next = size = std::vector<int>(n);

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
    first_dfs(first_dfs, r, r);

    int k = 0;
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
    second_dfs(second_dfs, r, r);
    return *this;
  }

private:
  int n;
  std::vector<std::vector<int>> g;
};
