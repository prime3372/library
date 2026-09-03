#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include "ds/implicit_treap_monoid.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

ll op(ll x, ll y) { return x + y; }
ll e() { return 0; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (ll& ai : a) cin >> ai;
  implicit_treap_monoid<ll, op, e> tp(a);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) tp.reverse(l, r);
    else cout << tp.prod(l, r) << "\n";
  }
}