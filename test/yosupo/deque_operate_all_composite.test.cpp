#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"

#include "../../algebra/Affine.hpp"
#include "../../ds/slide_window_aggregation_deque.hpp"
#include "../../util/static_modint.hpp"
#include <bits/stdc++.h>

using namespace std;
using mint = modint998244353;
using M = Affine<mint>;
using S = typename M::S;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  slide_window_aggregation_deque<M> swag;
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      mint a, b;
      cin >> a >> b;
      swag.push_front({a, b});
    } else if (t == 1) {
      mint a, b;
      cin >> a >> b;
      swag.push_back({a, b});
    } else if (t == 2) {
      swag.pop_front();
    } else if (t == 3) {
      swag.pop_back();
    } else {
      mint x;
      cin >> x;
      S f = swag.prod();
      cout << f.a * x + f.b << "\n";
    }
  }
}
