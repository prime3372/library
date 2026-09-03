#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include "ds/segtree.hpp"
#include "util/static_modint.hpp"
#include "tree/hl_decomposition.hpp"
#include <iostream>
#include <vector>

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;
using mint = modint998244353;

struct S {
  mint a, b;
};
S op(S f, S g) { return {g.a * f.a, g.a * f.b + g.b}; }
S rop(S g, S f) { return {g.a * f.a, g.a * f.b + g.b}; }
S e() { return {1, 0}; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  for (auto& f : a) cin >> f.a >> f.b;
  hl_decomposition hld(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    hld.add_edge(u, v);
  }
  hld.build();
  auto& ord = hld.ord;
  auto& head = hld.head;
  auto& next = hld.next;
  segtree<S, op, e> seg(n);
  segtree<S, rop, e> rseg(n);
  for (int i = 0; i < n; i++) {
    seg.set(ord[i], a[i]);
    rseg.set(ord[i], a[i]);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int p;
      mint c, d;
      cin >> p >> c >> d;
      seg.set(ord[p], {c, d});
      rseg.set(ord[p], {c, d});
    } else {
      int u, v;
      mint x;
      cin >> u >> v >> x;
      u = ord[u];
      v = ord[v];
      S l = {1, 0}, r = {1, 0};
      while (head[u] != head[v]) {
        if (u < v) {
          r = op(seg.prod(head[v], v + 1), r);
          v = next[v];
        } else {
          l = op(l, rseg.prod(head[u], u + 1));
          u = next[u];
        }
      }
      if (u < v) {
        r = op(seg.prod(u, v + 1), r);
      } else {
        l = op(l, rseg.prod(v, u + 1));
      }
      S f = op(l, r);
      cout << f.a * x + f.b << "\n";
    }
  }
}