#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "ds/treap_acted_monoid.hpp"
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
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].val;
    a[i].len = 1;
  }
  treap_acted_monoid<S, op, e, F, act, compose, id> tp(a);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int i;
      mint x;
      cin >> i >> x;
      tp.insert(i, {x, 1});
    } else if (t == 1) {
      int i;
      cin >> i;
      tp.erase(i);
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      tp.reverse(l, r);
    } else if (t == 3) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      tp.apply(l, r, {b, c});
    } else if (t == 4) {
      int l, r;
      cin >> l >> r;
      cout << tp.prod(l, r).val << "\n";
    }
  }
}