#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include "algebra/add.hpp"
#include "ds/treap_monoid.hpp"
#include <iostream>

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
  treap_monoid<alg::add<ll>> seg(a);
  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 0) seg.reverse(l, r);
    else cout << seg.prod(l, r) << "\n";
  }
}