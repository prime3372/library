#define PROBLEM "https://judge.yosupo.jp/problem/range_set_range_composite"

#include "algebra/affine.hpp"
#include "algebra/assign.hpp"
#include "ds/lazy_segtree.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;
using M = alg::assign<alg::affine<mint>>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<M::S> f(n);
  for (auto& fi : f) {
    cin >> fi.val.a >> fi.val.b;
    fi.len = 1;
  }
  lazy_segtree<M> seg(f);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int l, r;
      mint c, d;
      cin >> l >> r >> c >> d;
      seg.apply(l, r, {{c, d}, false});
    } else {
      int l, r;
      mint x;
      cin >> l >> r >> x;
      cout << seg.prod(l, r).val(x) << "\n";
    }
  }
}