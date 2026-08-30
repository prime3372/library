#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"

#include "ds/lazy_segtree.hpp"
#include <iostream>

using namespace std;
using namespace cp;

struct S {
  int val, len;
};
S op(S x, S y) { return {x.val + y.val, x.len + y.len}; }
S e() { return {0, 0}; }
S act(int f, S x) { return f == -1001 ? x : S{f * x.len, x.len}; }
int compose(int g, int f) { return g == -1001 ? f : g; }
int id() { return -1001; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  lazy_segtree<S, op, e, int, act, compose, id> seg(n, {0, 1});
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
      cout << seg.prod(s, t + 1).val << "\n";
    }
  }
}