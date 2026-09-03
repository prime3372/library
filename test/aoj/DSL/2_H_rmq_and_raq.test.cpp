#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"

#include "ds/lazy_segtree.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int op(int x, int y) { return min(x, y); }
int e() { return int(1e9); }
int act(int f, int x) { return x + f; }
int compose(int g, int f) { return g + f; }
int id() { return 0; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  lazy_segtree<int, op, e, int, act, compose, id> seg(n, 0);
  while (q--) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      seg.apply(s, t + 1, x);
    } else {
      int s, t;
      cin >> s >> t;
      cout << seg.prod(s, t + 1) << "\n";
    }
  }
}