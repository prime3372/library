#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"

#include "algebra/min_add.hpp"
#include "ds/lazy_segtree.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (ll& ai : a) cin >> ai;
  lazy_segtree<alg::min_add<ll, ll(1e18)>> seg(a);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
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