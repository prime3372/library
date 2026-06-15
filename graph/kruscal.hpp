#pragma once

#include <cassert>
#include <utility>
#include <vector>
#include "../ds/union_find.hpp"

template <class T> struct kruscal {
  using edge = std::tuple<T, int, int, int>;
 public:
  kruscal() : kruscal(0) {}
  explicit kruscal(int _n) : n(_n) {}

  int add_edge(int u, int v, T cost) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    int m = int(edges.size());
    edges.emplace_back(cost, m, u, v);
    return m;
  }

  std::pair<T, std::vector<int>> min() {
    std::sort(edges.begin(), edges.end());
    return greedy();
  }

  std::pair<T, std::vector<int>> max() {
    std::sort(edges.rbegin(), edges.rend());
    return greedy();
  }

private:
  int n;
  std::vector<edge> edges;
  std::vector<int> tree;

  std::pair<T, std::vector<int>> greedy() {
    T cost = 0;
    union_find uf(n);
    tree.clear();
    for (auto [c, id, u, v] : edges) {
      if (!uf.same(u, v)) {
        uf.unite(u, v);
        cost += c;
        tree.push_back(id);
      }
    }
    return {cost, tree};
  }
};
