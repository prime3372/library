#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include "../../ds/union_find_with_potential.hpp"
#include "../../util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  union_find_with_potential<mint> uf(n);
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
      if (!uf.same(u, v)) cout << -1 << "\n";
      else cout << uf.diff(u, v) << "\n";
    }  
  }
}
