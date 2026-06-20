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
  auto par = hld.parent, in = hld.in, rin = in, head = hld.head;  
  rep(i, 0, n) rin[i] = n - 1 - rin[i];
  segtree<M> seg(n), rseg(n);
  rep(i, 0, n) {
    seg.set(in[i], f[i]);
    rseg.set(rin[i], f[i]);
  }
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int p;
      mint c, d;
      cin >> p >> c >> d;
      seg.set(in[p], {c, d});
      rseg.set(rin[p], {c, d});
    } else {
      int u, v;
      mint x;
      cin >> u >> v >> x;
      M::S l = {1, 0}, r = {1, 0};
      while (head[u] != head[v]) {
        if (in[u] < in[v]) {
          r = M::op(seg.prod(in[head[v]], in[v] + 1), r);
          v = par[head[v]];
        } else {
          l = M::op(l, rseg.prod(rin[u], rin[head[u]] + 1));
          u = par[head[u]];
        }
      }
      if (in[u] < in[v]) {
        l = M::op(l, seg.prod(in[u], in[v] + 1));
      } else {
        l = M::op(l, rseg.prod(rin[u], rin[v] + 1));
      }
      M::S ans = M::op(l, r);
      cout << ans.a * x + ans.b << "\n";
    }
  }
}
