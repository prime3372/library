#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"

#include "../../algebra/Min_Add.hpp"
#include "../../ds/lazy_segtree.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  rep(i, 0, n) cin >> a[i];
  lazy_segtree<Min_Add<ll, ll(1e18)>> seg(a);
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int l, r;
      ll x;
      cin >> l >> r >> x;
      seg.apply(l, r, x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.prod(l, r) << "\n";
    }
  }
}
