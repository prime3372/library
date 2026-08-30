#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite_large_array"

#include "ds/dynamic_segtree.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

struct S {
  mint a, b;
};
static S op(S f, S g) { return {g.a * f.a, g.a * f.b + g.b}; }
static S e() { return {1, 0}; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  dynamic_segtree<S, op, e> seg(n);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int p;
      mint c, d;
      cin >> p >> c >> d;
      seg.set(p, {c, d});
    } else {
      int l, r;
      mint x;
      cin >> l >> r >> x;
      S f = seg.prod(l, r);
      cout << f.a * x + f.b << "\n";
    }
  }
}