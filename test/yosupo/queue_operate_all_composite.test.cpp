#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "../../algebra/affine.hpp"
#include "../../ds/slide_window_aggregation.hpp"
#include "../../util/static_modint.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;
using mint = modint998244353;
using M = affine<mint>;
using S = affine<mint>::S;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  slide_window_aggregation<M> swag;
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      mint a, b;
      cin >> a >> b;
      swag.push({a, b});
    } else if (t == 1) {
      swag.pop();
    } else {
      mint x;
      cin >> x;
      S f = swag.prod();
      cout << f.a * x + f.b << "\n";
    }
  }
}
