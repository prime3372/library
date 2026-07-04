#pragma once

#include <utility>
#include <vector>

namespace cp {

struct euler_tour {
public:
  euler_tour() : euler_tour(0) {}
  explicit euler_tour(int _n) : tour(_n, -1), in(_n, -1), out(_n, -1), n(_n), g(_n) {}

  void add_edge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    g[a].push_back(b);
    g[b].push_back(a);
  }

  std::vector<int> tour, in, out;

  euler_tour& build(int r = 0) {
    assert(0 <= r && r < n);
    auto dfs = [&](auto self, int v, int pv) -> void {
      in[v] = k;
      tour[k++] = v;
      for (int nv : g[v]) {
        if (nv == pv) continue;
        self(self, nv, v);
      }
      out[v] = k;
    };
    dfs(dfs, r, -1);
    return *this;
  }

private:
  int n, k = 0;
  std::vector<std::vector<int>> g;
};

} // namespace cp