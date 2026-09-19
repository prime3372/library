#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "ds/rectangle_sum.hpp"
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
  rectangle_sum<int, ll> sum;
  for (int i = 0; i < n; i++) {
    int x, y;
    ll w;
    cin >> x >> y >> w;
    sum.add_point(x, y, w);
  }
  sum.init();
  while (q--) {
    int l, d, r, u;
    cin >> l >> d >> r >> u;
    cout << sum.sum(l, d, r, u) << "\n";
  }
}