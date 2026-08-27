#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"

#include "ds/fenwick_tree.hpp"
#include "tree/centroid_decomposition.hpp"
#include "tree/lowest_common_ancestor.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (ll& ai : a) cin >> ai;
  vector<vector<int>> tree(n);
  centroid_decomposition cd(n);
  lowest_common_ancestor lca(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
    cd.add_edge(u, v);
    lca.add_edge(u, v);
  }
  cd.build();
  lca.init();

  vector<fenwick_tree<ll>> contour(n), contour_par(n);
  for (int i = 0; i < n; i++) {
    contour[i] = contour_par[i] = fenwick_tree<ll>(cd.size[i] + 1);
  }

  auto query0 = [&](int p, ll x) -> void {
    int cur = p;
    while (true) {
      contour[cur].add(lca.dist(cur, p), x);
      int par = cd.parent[cur];
      if (par == -1) break;
      contour_par[cur].add(lca.dist(par, p), x);
      cur = par;
    }
  };
  auto query1 = [&](int p, int r) -> ll {
    ll ans = 0;
    int cur = p;
    while (true) {
      int d1 = lca.dist(cur, p);
      if (r - d1 > 0) {
        ans += contour[cur].sum(min(r - d1, contour[cur].size()));
      }
      int par = cd.parent[cur];
      if (par == -1) break;
      int d2 = lca.dist(par, p);
      if (r - d2 > 0) {
        ans -= contour_par[cur].sum(min(r - d2, contour_par[cur].size()));
      }
      cur = par;
    }
    return ans;
  };

  for (int i = 0; i < n; i++) query0(i, a[i]);

  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
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