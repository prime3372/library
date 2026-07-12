#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

struct low_link {
public:
  low_link() : low_link(0) {}
  explicit low_link(int _n) : low(_n, _n), ord(_n, -1), n(_n), g(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  std::vector<int> low, ord;

  low_link& build() {
    int now_ord = 0;
    auto dfs = [&](auto self, int v, int pv) -> void {
      low[v] = ord[v] = now_ord++;
      bool multiple = false;
      for (int nv : g[v]) {
        if (nv == pv && !multiple) {
          multiple = true;
          continue;
        }
        if (ord[nv] == -1) {
          self(self, nv, v);
          low[v] = std::min(low[v], low[nv]);
        } else {
          low[v] = std::min(low[v], ord[nv]);
        }
      }
    };
    for (int i = 0; i < n; i++) {
      if (ord[i] == -1) dfs(dfs, i, -1);
    }
    return *this;
  }

protected:
  int n;
  std::vector<std::vector<int>> g;
};

}