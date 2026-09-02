#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "graph/max_flow.hpp"

namespace cp {

class bipartite_matching {
 public:
  bipartite_matching() : bipartite_matching(0, 0) {}
  explicit bipartite_matching(int _l, int _r)
      : l(_l), r(_r), s(l + r), t(l + r + 1), mf(l + r + 2) {
    for (int i = 0; i < l; i++) mf.add_edge(s, i);
    for (int i = 0; i < r; i++) mf.add_edge(l + i, t);
  }

  void add_edge(int a, int b) {
    assert(0 <= a && a < l);
    assert(0 <= b && b < r);
    mf.add_edge(a, l + b);
  }

  int max_matching() { return mf.flow(s, t); }

  std::vector<std::pair<int, int>> edges() {
    std::vector<std::pair<int, int>> res;
    for (auto&& e : mf.edges()) {
      if (e.from == s || e.to == t) continue;
      if (e.flow) res.emplace_back(e.from, e.to - l);
    }
    return res;
  }

 private:
  int l, r, s, t;
  max_flow<int> mf;
};

}  // namespace cp