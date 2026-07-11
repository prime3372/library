#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include "poly/formal_power_series.hpp"
#include "tree/centroid_decomposition.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;
  std::vector<std::vector<int>> g(n);
  centroid_decomposition cd(n);
  rep(i, 0, n - 1) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
    cd.add_edge(a, b);
  }
  cd.build();

  formal_power_series<ll> freq(n);
  vector<bool> removed(n);
  rep(i, 0, n) {
    int c = cd.centroid[i];
    int k = int(g[c].size());

    vector<formal_power_series<ll>> f(k);
    rep(i, 0, k) {
      auto dfs = [&](auto self, int v, int pv, int d) -> void {
        f[i][d]++;
        for (int nv : g[v]) {
          if (!removed[nv] && nv != pv) {
            self(self, nv, v, d + 1);
          }
        }
      };
      if (!removed[g[c][i]]) dfs(dfs, g[c][i], c, 1);
    }

    formal_power_series<ll> fsum, f2sum;
    rep(i, 0, k) fsum += f[i];
    rep(i, 0, k) f2sum += f[i] * f[i];
    freq += (fsum * fsum - f2sum) / 2 + fsum;

    removed[c] = true;
  };
  
  rep(i, 1, n) cout << freq[i] << " ";
}