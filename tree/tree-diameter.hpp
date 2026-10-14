#pragma once

#include <cassert>
#include <utility>
#include <vector>

namespace cp {

template <class T> struct TreeDiameter {
 public:
  TreeDiameter() : n(0) {}
  explicit TreeDiameter(int _n) : n(_n), g(_n) {}

  int add_edge(int u, int v, T c = 1) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    int m = int(co.size());
    co.push_back(c);
    g[u].push_back(Edge{v, m, c});
    g[v].push_back(Edge{u, m, c});
    return m;
  }

  int farthest(int s) { return farthest(s, -1).second; }

  T dist = 0;
  std::vector<int> vertices, edges;

  TreeDiameter& build(int s = 0) {
    assert(0 <= s && s < n);
    vertices.clear();
    edges.clear();

    int t = farthest(s), u = farthest(t);
    auto construct = [&](auto self, int v, int pv) -> bool {
      vertices.push_back(v);
      if (v == u) return true;
      for (auto e : g[v]) {
        if (e.to == pv) continue;
        edges.push_back(e.id);
        if (self(self, e.to, v)) return true;
        edges.pop_back();
      }
      vertices.pop_back();
      return false;
    };
    construct(construct, t, -1);

    dist = 0;
    for (int i : edges) dist += co[i];
    return *this;
  }

 private:
  struct Edge {
    int to, id;
    T cost;
  };

  int n;
  std::vector<T> co;
  std::vector<std::vector<Edge>> g;

  std::pair<T, int> farthest(int v, int pv) {
    std::pair<T, int> res = {0, v};
    for (auto e : g[v]) {
      if (e.to == pv) continue;
      auto p = farthest(e.to, v);
      p.first += e.cost;
      if (p > res) res = p;
    }
    return res;
  };
};

}  // namespace cp