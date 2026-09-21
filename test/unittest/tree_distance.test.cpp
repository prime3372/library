#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "random/random_tree.hpp"
#include "tree/tree_distance.hpp"
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

#include "tree/lowest_common_ancestor.hpp"

void test(int n, int q) {
  auto tree = random_tree(n);
  vector<vector<pair<int, ll>>> g(n);
  tree_distance<ll> dist(n);
  for (auto [u, v] : tree) {
    ll w = uniform(ll(-1e9), ll(1e9));
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
    dist.add_edge(u, v, w);
  }
  dist.init();
  while (q--) {
    int s = uniform(0, n - 1);
    int t = uniform(0, n - 1);
    ll d = 0;
    auto dfs = [&](auto self, int v, int pv) -> bool {
      if (v == t) return true;
      for (auto [nv, c] : g[v]) {
        if (nv != pv) {
          d += c;
          if (self(self, nv, v)) return true;
          d -= c;
        }
      }
      return false;
    };
    dfs(dfs, s, -1);
    assert(dist(s, t) == d);
  }
}
void small() { test(uniform(1, 100), 1000); }
void medium() { test(uniform(1, 1000), 1000); }
void large() { test(uniform(1, 100000), 10); }


int main() {
  for (int i = 0; i < 100; i++) small();
  for (int i = 0; i < 10; i++) medium();
  for (int i = 0; i < 10; i++) large();
  cout << "Hello World\n";
}