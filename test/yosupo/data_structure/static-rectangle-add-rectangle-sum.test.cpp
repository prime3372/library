#define PROBLEM "https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum"

#include "ds/static-rectangle-add-rectangle-sum.hpp"
#include "util/static-modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  StaticRectangleAddRectangleSum<int, mint> sum;
  for (int i = 0; i < n; i++) {
    int l, d, r, u;
    mint w;
    cin >> l >> d >> r >> u >> w;
    sum.add(l, d, r, u, w);
  }
  for (int i = 0; i < q; i++) {
    int l, d, r, u;
    cin >> l >> d >> r >> u;
    sum.sum(l, d, r, u);
  }
  auto ans = sum.run();
  for (int i = 0; i < q; i++) cout << ans[i] << "\n";
}