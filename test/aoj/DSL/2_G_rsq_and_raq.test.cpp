#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G"

#include "algebra/sum_add.hpp"
#include "ds/lazy_segtree.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;
using M = alg::sum_add<ll>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  lazy_segtree<M> seg(n, {0, 1});
  while (q--) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t;
      ll x;
      cin >> s >> t >> x;
      seg.apply(s - 1, t, x);
    } else {
      int s, t;
      cin >> s >> t;
      cout << seg.prod(s - 1, t) << "\n";
    }
  }
}