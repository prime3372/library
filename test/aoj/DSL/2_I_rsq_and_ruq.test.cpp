#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"

#include "algebra/sum_assign.hpp"
#include "ds/lazy_segtree.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using M = alg::sum_assign<int>;

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
      int s, t, x;
      cin >> s >> t >> x;
      seg.apply(s, t + 1, {x});
    } else {
      int s, t;
      cin >> s >> t;
      cout << seg.prod(s, t + 1) << "\n";
    }
  }
}