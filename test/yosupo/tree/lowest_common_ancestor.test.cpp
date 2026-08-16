#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "tree/tree_lca.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  tree_lca g(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    g.add_edge(i, p);
  }
  g.init();
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << g.lca(u, v) << "\n";
  }
}