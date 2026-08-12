#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include "algebra/add.hpp"
#include "ds/segtreap.hpp"

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
  segtreap<alg::add<ll>> seg(a);
  while (q--) {
    bool t;
    cin >> t;
    int l, r;
    cin >> l >> r;
    if (!t) seg.reverse(l, r);
    else cout << seg.prod(l, r) << "\n";
  }
}