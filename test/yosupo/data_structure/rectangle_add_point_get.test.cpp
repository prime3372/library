#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"

#include "ds/coordinate_compression.hpp"
#include "ds/dynamic_fenwick_tree_2d.hpp"
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<array<ll, 5>> data(n);
  for (auto& [l, d, r, u, w] : data) {
    cin >> l >> d >> r >> u >> w;
  }
  vector<array<ll, 5>> query(q);
  vector<ll> xs, ys;
  vector<int> t(q);
  for (int i = 0; i < q; i++) {
    cin >> t[i];
    if (t[i] == 0) {
      auto& [l, d, r, u, w] = query[i];
      cin >> l >> d >> r >> u >> w;
    } else {
      auto& x = query[i][0], y = query[i][1];
      cin >> x >> y;
      xs.push_back(x);
      ys.push_back(y);
    }
  }

  coordinate_compression cx(xs), cy(ys);
  dynamic_fenwick_tree_2d<ll> fw(cx.size(), cy.size());
  for (auto [l, d, r, u, w] : data) {
    fw.dual_add(cx(l), cy(d), cx(r), cy(u), w);
  }
  for (int i = 0; i < q; i++) {
    if (t[i] == 0) {
      auto [l, d, r, u, w] = query[i];
      fw.dual_add(cx(l), cy(d), cx(r), cy(u), w);
    } else {
      auto& x = query[i][0], y = query[i][1];
      cout << fw.dual_get(cx(x), cy(y)) << "\n";
    }
  }
}