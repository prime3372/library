#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "ds/lazy_segtree.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

struct S {
  mint val;
  int len;
};
S op(S x, S y) { return {x.val + y.val, x.len + y.len}; }
S e() { return {0, 0}; }
struct F {
  mint a, b;
};
S act(F f, S x) { return {f.a * x.val + f.b * x.len, x.len}; }
F compose(F g, F f) { return {g.a * f.a, g.a * f.b + g.b}; }
F id() { return {1, 0}; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  for (auto& ai : a) {
    cin >> ai.val;
    ai.len = 1;
  }
  lazy_segtree<S, op, e, F, act, compose, id> seg(a);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      seg.apply(l, r, {b, c});
    } else {
      int p;
      cin >> p;
      cout << seg[p].val << "\n";
    }
  }
}