#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "ds/fenwick_tree.hpp"
#include "tree/hl_decomposition.hpp"
#include <iostream>
#include <utility>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  hl_decomposition hld(n);
  for (ll& ai : a) cin >> ai;
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    hld.add_edge(u, v);
  }
  hld.build();
  auto id = hld.id, head = hld.head, next = hld.next;
  fenwick_tree<ll> fw(n);
  for (int i = 0; i < n; i++) fw.add(id[i], a[i]);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int p;
      ll x;
      cin >> p >> x;
      fw.add(id[p], x);
    } else {
      int u, v;
      cin >> u >> v;
      u = id[u];
      v = id[v];
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