#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

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
  vector<ll> x(n + q), y(n + q), w(n + q), l(q), d(q), r(q), u(q);
  vector<int> t(q);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i] >> w[i];
  }
  for (int i = 0; i < q; i++) {
    cin >> t[i];
    if (t[i] == 0) {
      cin >> x[n + i] >> y[n + i] >> w[n + i];
    } else {
      cin >> l[i] >> d[i] >> r[i] >> u[i];
    }
  }

  coordinate_compression comp_x(x), comp_y(y);
  dynamic_fenwick_tree_2d<ll> fw(comp_x.size() + 1, comp_y.size() + 1);
  auto cx = comp_x(x), cy = comp_y(y);
  auto cl = comp_x(l), cd = comp_y(d), cr = comp_x(r), cu = comp_y(u);
  for (int i = 0; i < n; i++) {
    fw.add(cx[i], cy[i], w[i]);
  }
  for (int i = 0; i < q; i++) {
    if (t[i] == 0) {
      fw.add(cx[n + i], cy[n + i], w[n + i]);
    } else {
      cout << fw.sum(cl[i], cd[i], cr[i], cu[i]) << "\n";
    }
  }
}