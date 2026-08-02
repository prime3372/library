#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "ds/fenwick_tree.hpp"
#include "tree/hl_decomposition.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  std::vector<ll> a(n);
  hl_decomposition hld(n);
  rep(i, 0, n) cin >> a[i];
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    hld.add_edge(u, v);
  }
  hld.build();
  auto id = hld.id, head = hld.head, next = hld.next;
  fenwick_tree<ll> fw(n);
  rep(i, 0, n) fw.add(id[i], a[i]);
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int p;
      ll x;
      cin >> p >> x;
      fw.add(id[p], x);
    } else {
      int u, v;
      cin >> u >> v;
      u = id[u]; v = id[v];
      ll ans = 0;
      while (head[u] != head[v]) {
        if (u > v) swap(u, v);
        ans += fw.sum(head[v], v + 1);
        v = next[v];
      }
      if (u > v) swap(u, v);
      ans += fw.sum(u, v + 1);
      cout << ans << "\n";
    }
  }
}