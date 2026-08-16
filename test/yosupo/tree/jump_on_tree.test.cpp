#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

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
  for (int i = 0; i < n - 1; i++) {
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