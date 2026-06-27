#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "../../tree/tree_lca.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  tree_lca g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    g.add_edge(u, v);
  }
  g.init();
  while (q--) {
    int a, b, i;
    cin >> a >> b >> i;
    cout << g.jump(a, b, i) << "\n";
  }
}
