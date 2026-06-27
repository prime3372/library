#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"

#include "../../ds/fenwick_tree.hpp"
#include "../../tree/centroid_decomposition.hpp"
#include "../../tree/tree_lca.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  rep(i, 0, n) cin >> a[i];
  vector<vector<int>> tree(n);
  centroid_decomposition cd(n);
  tree_lca lca(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
    cd.add_edge(u, v);
    lca.add_edge(u, v);
  }
  cd.build();
  lca.init();

  vector<fenwick_tree<ll>> fw_all(n), fw_par(n);
  rep(i, 0, n) {
    fw_all[i] = fw_par[i] = fenwick_tree<ll>(cd.size[i] + 1);
  }

  auto query0 = [&](int v, ll x) -> void {
    int cur = v;
    while (true) {
      fw_all[cur].add(lca.dist(cur, v), x);

      int par = cd.parent[cur];
      if (par == -1) break;
      fw_par[cur].add(lca.dist(par, v), x);
      cur = par;
    }
  };
  auto query1 = [&](int v, int r) -> ll {
    ll ans = 0;
    int cur = v;
    while (true) {
      int dcur = lca.dist(cur, v);
      if (r - dcur > 0) {
        ans += fw_all[cur].sum(min(r - dcur, fw_all[cur].size()));
      }

      int par = cd.parent[cur];
      if (par == -1) break;
      int dpar = lca.dist(par, v);
      if (r - dpar > 0) {
        ans -= fw_par[cur].sum(min(r - dpar, fw_all[cur].size()));
      }
      cur = par;
    }
    return ans;
  };

  rep(i, 0, n) query0(i, a[i]);  

  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int p;
      ll x;
      cin >> p >> x;
      query0(p, x);
    } else {
      int p, l, r;
      cin >> p >> l >> r;
      cout << query1(p, r) - query1(p, l) << "\n";
    }
  }
}
