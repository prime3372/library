#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "tree/lowest_common_ancestor.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  lowest_common_ancestor lca(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    lca.add_edge(u, v);
  }
  lca.init();
  while (q--) {
    int a, b, i;
    cin >> a >> b >> i;
    cout << lca.jump(a, b, i) << "\n";
  }
}