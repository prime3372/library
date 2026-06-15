#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "../../algebra/Sum_Affine.hpp"
#include "../../ds/lazy_segtree.hpp"
#include "../../util/static_modint.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using mint = modint998244353;
using M = Sum_Affine<mint>;
using S = Sum_Affine<mint>::S;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  rep(i, 0, n) {
    cin >> a[i].val;
    a[i].len = 1;
  }
  lazy_segtree<M> seg(a);
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      seg.apply(l, r, {b, c});
    } else {
      int p;
      cin >> p;
      cout << seg[p].val << "\n";
    }
  }
}
