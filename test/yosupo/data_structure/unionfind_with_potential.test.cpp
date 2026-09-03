#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include "ds/weighted_union_find.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  weighted_union_find<mint> uf(n);
  while (q--) {
    int t;
    cin >> t;
    if (!t) {
      int u, v;
      mint x;
      cin >> u >> v >> x;
      cout << uf.unite(u, v, x) << "\n";
    } else {
      int u, v;
      cin >> u >> v;
      if (!uf.same(u, v)) {
        cout << -1 << "\n";
      } else {
        cout << uf.diff(u, v) << "\n";
      }
    }
  }
}