#define PROBLEM \
  "https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound"

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
  rectangle_sum<int, int> cnt;
  rectangle_sum<int, ll> sum;
  for (int i = 0; i < n; i++) {
    int ai;
    cin >> ai;
    cnt.add_point(i, ai, 1);
    sum.add_point(i, ai, ai);
  }
  cnt.init();
  sum.init();
  while (q--) {
    int l, r, x;
    cin >> l >> r >> x;
    cout << cnt.lower_sum(l, r, x + 1) << " ";
    cout << sum.lower_sum(l, r, x + 1) << "\n";
  }
}