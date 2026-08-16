#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "algebra/sum_affine.hpp"
#include "ds/lazy_segtree.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;
using M = alg::sum_affine<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<M::S> a(n);
  for (auto& ai : a) {
    cin >> ai.val;
    ai.len = 1;
  }
  lazy_segtree<M> seg(a);
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