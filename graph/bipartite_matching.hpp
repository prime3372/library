#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "graph/max_flow.hpp"

namespace cp {

struct bipartite_matching {
public: 
  bipartite_matching() : bipartite_matching(0, 0) {}
  explicit bipartite_matching(int _l, int _r) : l(_l), r(_r), initialized(false), mf(_l + _r + 2), colored(_l + _r) {
    for (int i = 0; i < l; i++) mf.add_edge(l + r, i);
    for (int i = 0; i < r; i++) mf.add_edge(l + i, l + r + 1);
  }

  void add_edge(int a, int b) {
    assert(0 <= a && a < l);
    assert(0 <= b && b < r);
    mf.add_edge(a, l + b);
  }

  int init() {
    int f = mf.flow(l + r, l + r + 1);
    paint();
    initialized = true;
    return f;
  }

  struct edge {
    int from, to;
  };

  std::vector<edge>  max_matching() {
    if (!initialized) init();
    std::vector<edge> res;
    for (auto e : mf.edges()) {
      if (e.from == l + r || e.to == l + r + 1) continue;
      if (e.flow) res.push_back(edge{e.from, e.to - l});
    }
    return res;
  }

  std::pair<std::vector<int>, std::vector<int>> min_vertex_cover() {
    if (!initialized) init();
    std::vector<int> nl, nr;
    for (int i = 0; i < l; i++) {
      if (!colored[i]) nl.push_back(i);
    }
    for (int i = 0; i < r; i++) {
      if (colored[l + i]) nr.push_back(i);
    }
    return {nl, nr};
  }

  std::pair<std::vector<int>, std::vector<int>> max_independet_set() {
    if (!initialized) init();
    std::vector<int> nl, nr;
    for (int i = 0; i < l; i++) {
      if (colored[i]) nl.push_back(i);
    }
    for (int i = 0; i < r; i++) {
      if (!colored[l + i]) nr.push_back(i);
    }
    return {nl, nr};
  }

  std::vector<edge> min_edge_cover() {
    auto es = max_matching();
    std::vector<bool> used(l + r);
    for (auto e : es) {
      used[e.from] = used[l + e.to] = true;
    }
    for (auto e : mf.edges()) {
      if (e.flow || e.from == l + r || e.to == l + r + 1) continue;
      if (used[e.from] == false || used[e.to] == false) {
        es.push_back(edge{e.from, e.to - l});
        used[e.from] = used[e.to] = true;
      }
    }
    return es;
  }

private:
  int l, r;
  bool initialized;
  max_flow<int> mf;
  std::vector<bool> colored;

  void paint() {
    std::vector<std::vector<int>> g(l + r);
    std::vector<bool> start(l, true);

    for (auto e : mf.edges()) {
      if (e.from == l + r || e.to == l + r + 1) continue;
      if (e.flow) {
        g[e.to].push_back(e.from);
        start[e.from] = false;
      } else {
        g[e.from].push_back(e.to);
      }
    }

    auto dfs = [&](auto self, int v) -> void {
      if (colored[v]) return;
      colored[v] = true;
      for (int nv : g[v]) self(self, nv);
    };
    for (int i = 0; i < l; i++) {
      if (start[i]) dfs(dfs, i);
    }
  }
};

} // namespace cp