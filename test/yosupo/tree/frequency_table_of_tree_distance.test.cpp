#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include "poly/formal_power_series_ll.hpp"
#include "tree/centroid_decomposition.hpp"
#include <iostream>
#include <vector>

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
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
    cd.add_edge(a, b);
  }
  cd.build();

  formal_power_series_ll freq(n);
  vector<bool> removed(n);
  for (int i = 0; i < n; i++) {
    int c = cd.centroid[i];
    int k = int(g[c].size());

    vector<formal_power_series_ll> f(k);
    for (int j = 0; j < k; j++) {
      auto dfs = [&](auto self, int v, int pv, int d) -> void {
        if (f[j].size() <= d) f[j].resize(d + 1);
        f[j][d]++;
        for (int nv : g[v]) {
          if (!removed[nv] && nv != pv) {
            self(self, nv, v, d + 1);
          }
        }
      };
      if (!removed[g[c][j]]) dfs(dfs, g[c][j], c, 1);
    }

    formal_power_series_ll fsum, f2sum;
    for (int j = 0; j < k; j++) fsum += f[j];
    for (int j = 0; j < k; j++) f2sum += f[j] * f[j];
    freq += (fsum * fsum - f2sum) / 2 + fsum;

    removed[c] = true;
  }
  
  for (int i = 1; i < n; i++) cout << freq[i] << " ";
}