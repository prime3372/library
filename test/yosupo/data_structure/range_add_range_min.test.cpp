#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"

#include "ds/lazy_segtree.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

ll op(ll x, ll y) { return min(x, y); }
ll e() { return ll(1e18); }
ll act(ll f, ll x) { return x + f; }
ll compose(ll g, ll f) { return g + f; }
ll id() { return 0; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (ll& ai : a) cin >> ai;
  lazy_segtree<ll, op, e, ll, act, compose, id> seg(a);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int l, r, x;
      cin >> l >> r >> x;
      seg.apply(l, r, x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.prod(l, r) << "\n";
    }
  }
}