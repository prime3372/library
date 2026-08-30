#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G"

#include "ds/lazy_segtree.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

struct S {
  ll val;
  int len;
};
S op(S x, S y) { return {x.val + y.val, x.len + y.len}; }
S e() { return {0, 0}; }
S act(ll f, S x) { return {x.val + f * x.len, x.len}; }
ll compose(ll g, ll f) { return g + f; }
ll id() { return 0; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  lazy_segtree<S, op, e, ll, act, compose, id> seg(n, {0, 1});
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
      cout << seg.prod(s - 1, t).val << "\n";
    }
  }
}