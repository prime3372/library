#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum_large_array"

#include "ds/dynamic_lazy_segtree.hpp"
#include "util/static_modint.hpp"
#include <iostream>

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
  size_t n;
  int q;
  cin >> n >> q;
  dynamic_lazy_segtree<S, op, e, F, act, compose, id> seg(n, S{0, 1});
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      seg.apply(l, r, {b, c});
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.prod(l, r).val << "\n";
    }
  }
}