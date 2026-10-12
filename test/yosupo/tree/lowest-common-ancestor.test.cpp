#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "tree/lowest-common-ancestor.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  lowest_common_ancestor lca(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    lca.add_edge(i, p);
  }
  lca.init();
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << "\n";
  }
}