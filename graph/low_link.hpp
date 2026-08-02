#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

struct low_link {
private:
  struct edge {
    int to, id;
  };

public:
  low_link() : low_link(0) {}
  explicit low_link(int _n) : low(_n, _n), ord(_n, -1), n(_n), g(_n) {}

  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    g[u].push_back(edge{v, m});
    g[v].push_back(edge{u, m});
    m++;
  }

  std::vector<int> low, ord;

  low_link& build() {
    int now_ord = 0;
    auto dfs = [&](auto self, int v, int pv) -> void {
      low[v] = ord[v] = now_ord++;
      bool multiple = false;
      for (auto& e : g[v]) {
        if (e.to == pv && !multiple) {
          multiple = true;
          continue;
        }
        if (ord[e.to] == -1) {
          self(self, e.to, v);
          low[v] = std::min(low[v], low[e.to]);
        } else {
          low[v] = std::min(low[v], ord[e.to]);
        }
      }
    };
    for (int i = 0; i < n; i++) {
      if (ord[i] == -1) dfs(dfs, i, -1);
    }
    return *this;
  }

protected:
  int n, m;
  std::vector<std::vector<edge>> g;
};

} // namespace cp