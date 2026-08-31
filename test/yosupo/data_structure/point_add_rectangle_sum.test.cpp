#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

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
  vector<array<ll, 3>> data(n);
  vector<ll> xs, ys;
  for (auto& [x, y, w] : data) {
    cin >> x >> y >> w;
    xs.push_back(x);
    ys.push_back(y);
  }
  vector<array<ll, 4>> query(q);
  vector<int> t(q);
  for (int i = 0; i < q; i++) {
    cin >> t[i];
    if (t[i] == 0) {
      auto& [x, y, w, _] = query[i];
      cin >> x >> y >> w;
      xs.push_back(x);
      ys.push_back(y);
    } else {
      auto& [l, d, r, u] = query[i];
      cin >> l >> d >> r >> u;
    }
  }

  coordinate_compression cx(xs), cy(ys);
  dynamic_fenwick_tree_2d<ll> fw(cx.size(), cy.size());
  for (int i = 0; i < n; i++) {
    auto [x, y, w] = data[i];
    fw.add(cx(x), cy(y), w);
  }
  for (int i = 0; i < q; i++) {
    if (t[i] == 0) {
      auto& [x, y, w, _] = query[i];
      fw.add(cx(x), cy(y), w);
    } else {
      auto& [l, d, r, u] = query[i];
      cout << fw.sum(cx(l), cy(d), cx(r), cy(u)) << "\n";
    }
  }
}