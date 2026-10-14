#pragma once

#include <cassert>
#include <vector>

#include "graph/strongly-connected-components.hpp"

namespace cp {

class TwoSat {
 public:
  TwoSat() : TwoSat(0) {}
  explicit TwoSat(int _n) : n(_n), scc(2 * _n) {}

  void add_clause(int i, bool f, int j, bool g) {
    assert(0 <= i && i < n);
    assert(0 <= j && j < n);
    scc.add_edge(2 * i + !f, 2 * j + g);
    scc.add_edge(2 * j + !g, 2 * i + f);
  }

  std::vector<bool> solve() {
    std::vector<bool> ans(n);
    scc.build();
    for (int i = 0; i < n; i++) {
      if (scc.id[2 * i] == scc.id[2 * i + 1]) return {};
      ans[i] = scc.id[2 * i] < scc.id[2 * i + 1];
    }
    return ans;
  }

 private:
  int n;
  StronglyConnectedComponents scc;
};

}  // namespace cp