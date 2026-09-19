#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "ds/offline_point_add_rectangle_sum.hpp"
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
  offline_point_add_rectangle_sum<int, ll> sum;
  for (int i = 0; i < n; i++) {
    int x, y;
    ll w;
    cin >> x >> y >> w;
    sum.add_point(x, y, w);
  }

  vector<int> t(q);
  vector<array<unsigned int, 4>> query(q);
  for (int i = 0; i < q; i++) {
    cin >> t[i];
    if (t[i] == 0) {
      auto& [x, y, w, a] = query[i];
      cin >> x >> y >> w;
      sum.add_point(x, y);
    } else {
      auto& [l, d, r, u] = query[i];
      cin >> l >> d >> r >> u;
    }
  }

  sum.init();

  for (int i = 0; i < q; i++) {
    if (t[i] == 0) {
      auto [x, y, w, a] = query[i];
      sum.add(x, y, w);
    } else {
      auto [l, d, r, u] = query[i];
      cout << sum.sum(l, d, r, u) << "\n";
    }
  }
}