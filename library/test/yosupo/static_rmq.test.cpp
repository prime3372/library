#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "algebra/min.hpp"
#include "ds/disjoint_sparse_table.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  rep(i, 0, n) cin >> a[i];
  disjoint_sparse_table<cp::min<int, int(1e9)>> dst(a);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << dst.prod(l, r) << "\n";
  }
}