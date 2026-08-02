#pragma once

#include <cassert>
#include <vector>

namespace cp {

int get_centroid(const std::vector<std::vector<int>>& g, int s = 0) {
  int n = int(g.size());
  assert(0 <= s && s < n);

  std::vector<int> sub(n);
  auto size = [&](auto self, int v, int pv) -> int {
    sub[v] = 1;
    for (int nv : g[v]) {
      assert(0 <= nv && nv < n);
      if (nv != pv) sub[v] += self(self, nv, v);
    }
    return sub[v];
  };
  size(size, s, -1);

  auto centroid = [&](auto self, int v, int pv) -> int {
    for (int nv : g[v]) {
      if (nv != pv && sub[nv] > n / 2) return self(self, nv, v);
    }
    return v;
  };
  return centroid(centroid, s, -1);
}

} // namespace cp