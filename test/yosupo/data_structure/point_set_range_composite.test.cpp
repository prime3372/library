#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "algebra/affine.hpp"
#include "ds/segtree.hpp"
#include "util/static_modint.hpp"
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;
using M = alg::affine<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<M::S> a(n);
  for (auto& ai : a) cin >> ai.a >> ai.b;
  segtree<M> seg(a);
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
      cout << seg.prod(l, r)(x) << "\n";
    }
  }
}