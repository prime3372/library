#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "ds/dynamic_fenwick_tree_2d.hpp"
#include "util/coordinate_compression.hpp"
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

  vector<ll> x(n + q), y(n + q), w(n + q), l(q), d(q), r(q), u(q);
  vector<int> t(q);
  for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> w[i];  
  for (int i = 0; i < q; i++) {
    cin >> t[i];
    if (!t[i]) cin >> x[n + i] >> y[n + i] >> w[n + i];
    else cin >> l[i] >> d[i] >> r[i] >> u[i];
  }

  coordinate_compression cc(x);
  dynamic_fenwick_tree_2d<ll> fw(cc.size() + 1, int(1e9) + 1);
  vector<int> cx = cc(x), cl = cc(l), cr = cc(r);
  for (int i = 0; i < n; i++) {
    fw.add(cx[i], y[i], w[i]);
  }
  for (int i = 0; i < q; i++) {
    if (!t[i]) fw.add(cx[n + i], y[n + i], w[n + i]);
    else cout << fw.sum(cl[i], d[i], cr[i], u[i]) << "\n";    
  }
}