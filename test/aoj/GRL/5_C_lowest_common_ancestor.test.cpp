#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_5_C"

#include "tree/lowest_common_ancestor.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  lowest_common_ancestor lca(n);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int c;
      cin >> c;
      lca.add_edge(i, c);
    }
  }
  lca.init();
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << "\n";
  }
}