#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite_large_array"

#include "../../algebra/Affine.hpp"
#include "../../ds/dynamic_segtree.hpp"
#include "../../util/static_modint.hpp"

#include <bits/stdc++.h>
using namespace std;
using mint = modint998244353;
using M = Affine<mint>;
using S = M::S;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  size_t n;
  int q;
  cin >> n >> q;
  dynamic_segtree<M> seg(n);
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
