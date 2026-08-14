#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum_large_array"

#include "algebra/sum_affine.hpp"
#include "ds/dynamic_lazy_segtree.hpp"
#include "util/static_modint.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;
using mint = modint998244353;
using M = alg::sum_affine<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  size_t n;
  int q;
  cin >> n >> q;
  dynamic_lazy_segtree<M> seg(n, {0, 1});
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