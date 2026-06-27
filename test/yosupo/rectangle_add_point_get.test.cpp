#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"

#include "../../ds/dynamic_fenwick_tree_2d.hpp"
#include "../../util/coordinate_compression.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;

  vector<ll> l(n + q), d(n + q), r(n + q), u(n + q), w(n + q), x(q), y(q);
  vector<int> t(q);
  rep(i, 0, n) {
    cin >> l[i] >> d[i] >> r[i] >> u[i] >> w[i];
  }
  rep(i, 0, q) {
    cin >> t[i];
    if (!t[i]) cin >> l[n + i] >> d[n + i] >> r[n + i] >> u[n + i] >> w[n + i];
    else cin >> x[i] >> y[i];
  }

  coordinate_compression ccx(x), ccy(y);
  dynamic_fenwick_tree_2d<ll> fw(ccx.size() + 1, ccy.size() + 1);
  vector<int> cx = ccx(x), cy = ccy(y), cl = ccx(l), cd = ccy(d), cr = ccx(r), cu = ccy(u);
  rep(i, 0, n) {
    fw.imos_add(cl[i], cd[i], cr[i], cu[i], w[i]);
  }
  rep(i, 0, q) {
    if (!t[i]) fw.imos_add(cl[n + i], cd[n + i], cr[n + i], cu[n + i], w[n + i]);
    else cout << fw.imos_get(cx[i], cy[i]) << "\n";    
  }
}
