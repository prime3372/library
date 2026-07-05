#pragma once

#include <cassert>
#include <vector>

#include "graph/scc_graph.hpp"

namespace cp {

struct two_sat {
public:
  two_sat() : two_sat(0) {}
  explicit two_sat(int _n) : n(_n), scc(2 * _n) {}

  void add_clause(int i, bool f, int j, bool g) {
    assert(0 <= i && i < n);
    assert(0 <= j && j < n);
    scc.add_edge(2 * i + !f, 2 * j + g);
    scc.add_edge(2 * j + !g, 2 * i + f);
  }

  std::vector<bool> solve() {
    std::vector<bool> ans(n);
    auto id = scc.scc_ids().second;
    for (int i = 0; i < n; i++) {
      if (id[2 * i] == id[2 * i + 1]) return {};
      ans[i] = id[2 * i] < id[2 * i + 1];
    }
    return ans;
  }

private:
  int n;
  scc_graph scc;
};

} // namespace cp