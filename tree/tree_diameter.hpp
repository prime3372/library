#pragma once

#include <cassert>
#include <utility>
#include <vector>

template <class T> struct tree_diameter {
public:
  tree_diameter(int n) : dist(0), n(n), g(n) {}
  
  int add_edge(int u, int v, T c = 1) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    int m = int(pos.size());
    pos.push_back(c);
    g[u].push_back(edge{m, v, c});
    g[v].push_back(edge{m, u, c});
    return m;
  }
  
  int farthest(int s) {
    return farthest(s, -1).second;
  }
  
  T dist;
  std::vector<int> vertices, edges;
  
  tree_diameter& build(int s = 0) {
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
    for (int i : edges) dist += pos[i];
    return *this;
  }
  
private:
  int n;
  struct edge {
    int id, to;
    T cost;
  };
  std::vector<T> pos;
  std::vector<std::vector<edge>> g;

  std::pair<T, int> farthest(int v, int pv) {
    std::pair<T, int> res{0, v};
    for (auto e : g[v]) {
      if (e.to == pv) continue;
      auto p = farthest(e.to, v);
      p.first += e.cost;
      if (p > res) res = p;
    }
    return res;
  };
};
