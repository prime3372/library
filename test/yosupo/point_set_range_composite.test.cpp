#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../../algebra/Affine.hpp"
#include "../../ds/segtree.hpp"
#include "../../util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using mint = modint998244353;
using M = Affine<mint>;
using S = Affine<mint>::S;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  rep(i, 0, n) cin >> a[i].a >> a[i].b;
  segtree<M> seg(a);
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int p;
      mint c, d;
      cin >> p >> c >> d;
      seg.set(p, {c, d});
    } else {
      int l, r;
      mint x;
      cin >> l >> r >> x;
      S f = seg.prod(l, r);
      cout << f.a * x + f.b << "\n";
    }
  }
}
