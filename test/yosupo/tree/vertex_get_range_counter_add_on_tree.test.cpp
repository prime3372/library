#define PROBLEM "https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree"

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

  auto query0 = [&](int p, int r, ll x) -> void {
    int cur = p;
    while (true) {
      int d1 = lca.dist(cur, p);
      if (r - d1 > 0) {
        contour[cur].dual_add(0, min(r - d1, contour[cur].size()), x);
      }
      int par = cd.parent[cur];
      if (par == -1) break;
      int d2 = lca.dist(par, p);
      if (r - d2 > 0) {
        contour_par[cur].dual_add(0, min(r - d2, contour_par[cur].size()), x);
      }
      cur = par;
    }
  };
  auto query1 = [&](int p) -> ll {
    ll ans = 0;
    int cur = p;
    while (true) {
      ans += contour[cur].dual_get(lca.dist(cur, p));
      int par = cd.parent[cur];
      if (par == -1) break;
      ans -= contour_par[cur].dual_get(lca.dist(par, p));
      cur = par;
    }
    return ans;
  };

  for (int i = 0; i < n; i++) query0(i, 1, a[i]);

  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int p, l, r;
      ll x;
      cin >> p >> l >> r >> x;
      query0(p, r, x);
      query0(p, l, -x);
    } else {
      int p;
      cin >> p;
      cout << query1(p) << "\n";
    }
  }
}