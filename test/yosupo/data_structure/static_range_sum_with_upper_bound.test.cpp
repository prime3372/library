#define PROBLEM \
  "https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound"

#include "ds/rectangle_sum.hpp"
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;
using i128 = __int128;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  rectangle_sum<int, i128> sum;
  for (int i = 0; i < n; i++) {
    int ai;
    cin >> ai;
    sum.add_point(i, ai, (i128(1) << 64) + ai);
  }
  sum.init();
  while (q--) {
    int l, r, x;
    cin >> l >> r >> x;
    i128 ans = sum.query(l, 0, r, x + 1);
    cout << ll(ans >> 64) << " " << ll(ans & -1ULL) << "\n";
  }
}