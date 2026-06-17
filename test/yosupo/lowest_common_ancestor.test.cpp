#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../tree/doubling_lca.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  doubling_lca g(n);
  rep(i, 1, n) {
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
