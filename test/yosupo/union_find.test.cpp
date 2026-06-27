#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../ds/union_find.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  union_find uf(n);
  while (q--) {
    int t, u, v;
    cin >> t >> u >> v;
    if (!t) {
      uf.unite(u, v);
    } else {
      cout << uf.same(u, v) << "\n";
    }
  }
}
