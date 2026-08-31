#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"

#include "ds/coordinate_compression.hpp"
#include "ds/dynamic_fenwick_tree_2d.hpp"
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
  vector<ll> l(n + q), d(n + q), r(n + q), u(n + q), w(n + q), x(q), y(q);
  vector<int> t(q);
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> d[i] >> r[i] >> u[i] >> w[i];  
  }
  for (int i = 0; i < q; i++) {
    cin >> t[i];
    if (!t[i]) {
      cin >> l[n + i] >> d[n + i] >> r[n + i] >> u[n + i] >> w[n + i];
    } else {
      cin >> x[i] >> y[i];
    }
  }

  coordinate_compression comp_x(x), comp_y(y);
  dynamic_fenwick_tree_2d<ll> fw(comp_x.size() + 1, comp_y.size() + 1);
  auto cx = comp_x(x), cy = comp_y(y);
  auto cl = comp_x(l), cd = comp_y(d), cr = comp_x(r), cu = comp_y(u);
  for (int i = 0; i < n; i++) {
    fw.imos_add(cl[i], cd[i], cr[i], cu[i], w[i]);
  }
  for (int i = 0; i < q; i++) {
    if (!t[i]) {
      fw.imos_add(cl[n + i], cd[n + i], cr[n + i], cu[n + i], w[n + i]);
    } else {
      cout << fw.imos_get(cx[i], cy[i]) << "\n";
    }
  }
}