#define PROBLEM "https://judge.yosupo.jp/problem/range_set_range_composite"

#include "ds/lazy_segtree.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

struct S {
  mint a, b;
  int len;
};
S op(S x, S y) { return {y.a * x.a, y.a * x.b + y.b, x.len + y.len}; }
S e() { return {1, 0, 0}; }

struct F {
  mint a, b;
};
F power(F f, int n) {
  F g = {1, 0};
  while (n) {
    if (n & 1) g = {g.a * f.a, g.a * f.b + g.b};
    f = {f.a * f.a, f.a * f.b + f.b};
    n >>= 1;
  }
  return g;
}
S act(F f, S x) {
  if (f.a == 0) return x;
  auto g = power(f, x.len);
  return {g.a, g.b, x.len};
}
F compose(F g, F f) { return g.a == 0 ? f : g; }
F id() { return {0, 0}; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  for (auto& x : a) {
    cin >> x.a >> x.b;
    x.len = 1;
  }
  lazy_segtree<S, op, e, F, act, compose, id> seg(a);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int l, r;
      mint c, d;
      cin >> l >> r >> c >> d;
      seg.apply(l, r, {c, d});
    } else {
      int l, r;
      mint x;
      cin >> l >> r >> x;
      S f = seg.prod(l, r);
      cout << f.a * x + f.b << "\n";
    }
  }
}