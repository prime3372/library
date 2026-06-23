#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include "../../algebra/Affine.hpp"
#include "../../ds/segtree.hpp"
#include "../../util/static_modint.hpp"
#include "../../tree/hl_decomposition.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using mint = modint998244353;
using M = Affine<mint>;

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct _Affine {
  using S = M::S;
  static S op(S g, S f) { return {g.a * f.a, g.a * f.b + g.b}; }
  static S e() { return S(); }
};
using _M = _Affine<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  std::vector<M::S> f(n);
  rep(i, 0, n) cin >> f[i].a >> f[i].b;
  hl_decomposition hld(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    hld.add_edge(u, v);
  }
  hld.build();
  auto id = hld.id, head = hld.head, next = hld.next;
  segtree<M> seg(n);
  segtree<_M> rseg(n);
  rep(i, 0, n) {
    seg.set(id[i], f[i]);
    rseg.set(id[i], f[i]);
  }
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int p;
      mint c, d;
      cin >> p >> c >> d;
      seg.set(id[p], {c, d});
      rseg.set(id[p], {c, d});
    } else {
      int u, v;
      mint x;
      cin >> u >> v >> x;
      u = id[u]; v = id[v];
      M::S l = {1, 0}, r = {1, 0};
      while (head[u] != head[v]) {
        if (u < v) {
          r = M::op(seg.prod(head[v], v + 1), r);
          v = next[v];
        } else {
          l = M::op(l, rseg.prod(head[u], u + 1));
          u = next[u];
        }
      }
      if (u < v) r = M::op(seg.prod(u, v + 1), r);
      else l = M::op(l, rseg.prod(v, u + 1));
      M::S ans = M::op(l, r);
      cout << ans.a * x + ans.b << "\n";
    }
  }
}
