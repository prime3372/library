#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D"

#include "ds/lazy_segtree.hpp"
#include <climits>
#include <iostream>

using namespace std;
using namespace cp;

int op(int x, int y) { return min(x, y); }
int e() { return INT_MAX; }
int act(int f, int x) { return f == -1 ? x : f; }
int compose(int g, int f) { return g == -1 ? f : g; }
int id() { return -1; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  lazy_segtree<int, op, e, int, act, compose, id> seg(n);
  while (q--) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      seg.apply(s, t + 1, x);
    } else {
      int i;
      cin >> i;
      cout << seg[i] << "\n";
    }
  }
}