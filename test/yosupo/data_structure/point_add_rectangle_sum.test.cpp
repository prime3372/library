#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "ds/fenwick_tree.hpp"
#include "ds/wavelet_matrix.hpp"
#include "util/algo_utility.hpp"
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;

  vector<unsigned> xs, ys;
  vector<ll> ws;

  vector<tuple<unsigned int, unsigned int, ll>> init(n);
  for (auto& [x, y, w] : init) {
    cin >> x >> y >> w;
    xs.push_back(x);
    ys.push_back(y);
    ws.push_back(w);
  }

  vector<int> t(q);
  vector<array<unsigned int, 4>> query(q);
  for (int i = 0; i < q; i++) {
    cin >> t[i];
    if (t[i] == 0) {
      auto& [x, y, w, a] = query[i];
      cin >> x >> y >> w;
      xs.push_back(x);
      ys.push_back(y);
      ws.push_back(w);
    } else {
      auto& [l, d, r, u] = query[i];
      cin >> l >> d >> r >> u;
    }
  }

  int m = int(xs.size());
  auto p = sort(xs);
  vector<int> ip(p.size());
  for (int i = 0; i < int(p.size()); i++) ip[p[i]] = i;

  wavelet_matrix<unsigned int> wm(m);
  for (int i = 0; i < m; i++) wm.set(i, ys[p[i]]);
  wm.build();

  vector<fenwick_tree<ll>> fw(32, fenwick_tree<ll>(m + 1));
  for (int i = 0; i < n; i++) {
    int k = ip[i];
    for (int h = 31; h >= 0; h--) {
      k = wm[h].next(k);
      fw[h].add(k, ws[i]);
    }
  }

  auto add = [&](int k, ll w) -> void {
    for (int h = 31; h >= 0; h--) {
      k = wm[h].next(k);
      fw[h].add(k, w);
    }
  };
  auto sum = [&](int l, int r, unsigned int u) -> ll {
    ll ans = 0;
    for (int h = 31; h >= 0; h--) {
      int l0 = wm[h].next0(l);
      int r0 = wm[h].next0(r);
      if ((u >> h) & 1) {
        ans += fw[h].sum(l0, r0);
        l = wm[h].next1(l);
        r = wm[h].next1(r);
      } else {
        l = l0;
        r = r0;
      }
    }
    return ans;
  };

  for (int i = 0, j = 0; i < q; i++) {
    if (t[i] == 0) {
      auto [x, y, w, a] = query[i];
      add(ip[n + j], w);
      j++;
    } else {
      auto [l, d, r, u] = query[i];
      int l_lb = int(std::lower_bound(xs.begin(), xs.end(), l) - xs.begin());
      int r_lb = int(std::lower_bound(xs.begin(), xs.end(), r) - xs.begin());
      cout << sum(l_lb, r_lb, u) - sum(l_lb, r_lb, d) << "\n";
    }
  }
}