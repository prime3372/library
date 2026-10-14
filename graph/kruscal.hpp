#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "ds/union-find.hpp"

namespace cp {

template <class T> struct Kruscal {
 public:
  Kruscal() : Kruscal(0) {}
  explicit Kruscal(int _n) : n(_n) {}

  int add_edge(int u, int v, T cost) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    int m = int(edges.size());
    edges.emplace_back(cost, u, v, m);
    return m;
  }

  T min() {
    std::sort(edges.begin(), edges.end());
    return greedy();
  }

  T max() {
    std::sort(edges.rbegin(), edges.rend());
    return greedy();
  }

  // @return Edge ids
  const std::vector<int>& mst() { return tree; }

 private:
  using Edge = std::tuple<T, int, int, int>;
  int n;
  std::vector<Edge> edges;
  std::vector<int> tree;

  T greedy() {
    T cost = 0;
    UnionFind uf(n);
    tree.clear();
    for (auto [c, u, v, id] : edges) {
      if (!uf.same(u, v)) {
        uf.unite(u, v);
        cost += c;
        tree.push_back(id);
      }
    }
    return cost;
  }
};

}  // namespace cp