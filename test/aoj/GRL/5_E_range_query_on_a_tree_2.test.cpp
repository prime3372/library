#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_5_E"

#include "ds/lazy_segtree.hpp"
#include "tree/hl_decomposition.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

struct S {
  ll val;
  int len;
};
S op(S x, S y) { return {x.val + y.val, x.len + y.len}; }
S e() { return {0, 0}; }
S act(ll f, S x) { return {x.val + f * x.len, x.len}; }
ll compose(ll g, ll f) { return g + f; }
ll id() { return 0; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  hl_decomposition hld(n);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int c;
      cin >> c;
      hld.add_edge(i, c);
    }
  }
  hld.build();

  int q;
  cin >> q;
  lazy_segtree<S, op, e, ll, act, compose, id> seg(n, {0, 1});
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int v;
      ll w;
      cin >> v >> w;
      v = hld.ord[v];
      while (v != -1) {
        seg.apply(hld.head[v], v + 1, w);
        v = hld.next[v];
      }
    } else {
      int u;
      cin >> u;
      u = hld.ord[u];
      ll ans = 0;
      while (u != -1) {
        ans += seg.prod(hld.head[u], u + 1).val;
        u = hld.next[u];
      }
      cout << ans - seg[0].val << "\n";
    }
  }
}