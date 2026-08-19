#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "algebra/sum_affine.hpp"
#include "ds/treap_acted_monoid.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;
using M = alg::sum_affine<mint>;

int main() {
  int n, q;
  cin >> n >> q;
  vector<M::S> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].val;
    a[i].len = 1;
  }
  treap_acted_monoid<M> tp(a);
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
      cout << tp.prod(l, r) << "\n";
    }
  }
}