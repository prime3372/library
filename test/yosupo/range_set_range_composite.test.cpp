#define PROBLEM "https://judge.yosupo.jp/problem/range_set_range_composite"

#include "../../algebra/affine.hpp"
#include "../../algebra/assign.hpp"
#include "../../ds/lazy_segtree.hpp"
#include "../../util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using mint = modint998244353;
using A = affine<mint>::S;
using M = assign<affine<mint>>;
using S = M::S;
using F = M::F;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<S> f(n);
  rep(i, 0, n) {
    mint a, b;
    cin >> a >> b;
    f[i] = {{a, b}, 1};
  }
  lazy_segtree<M> seg(f);
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int l, r;
      mint c, d;
      cin >> l >> r >> c >> d;
      seg.apply(l, r, F{A{c, d}});
    } else {
      int l, r;
      mint x;
      cin >> l >> r >> x;
      S prod = seg.prod(l, r);
      cout << prod.val.a * x + prod.val.b << "\n";
    }
  }
}
