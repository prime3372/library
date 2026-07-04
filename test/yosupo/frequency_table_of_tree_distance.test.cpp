#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include "poly/polynomial.hpp"
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
  centroid_decomposition cd(n);
  rep(i, 0, n - 1) {
    int a, b;
    cin >> a >> b;
    cd.add_edge(a, b);
  }
  cd.build();
  polynomial<ll> freq(n);
  rep(p, 0, n) {
    int dep = cd.depth[p];
    int k = int(cd.tree[p].size());
    vector<polynomial<ll>> f(k);
    rep(i, 0, k) {
      f[i].resize(cd.size[cd.tree[p][i]] + 1);
    }
    rep(i, 0, k) {
      auto dfs = [&](auto self, int v, int d) -> void {
        f[i][d]++;
        for (int nv : cd.subtrees[dep][v]) {
          self(self, nv, d + 1);
        }
      };
      dfs(dfs, cd.subtrees[dep][p][i], 1);
    }
    polynomial<ll> fsum, f2sum;
    rep(i, 0, k) fsum += f[i];
    rep(i, 0, k) f2sum += f[i] * f[i];
    freq += (fsum * fsum - f2sum) / 2 + fsum;
  }
  rep(i, 1, n) cout << freq[i] << " ";
}