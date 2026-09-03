#define PROBLEM \
  "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include "poly/convolution_ll.hpp"
#include "tree/centroid_decomposition.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void operator+=(vector<ll>& a, const vector<ll>& b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < int(b.size()); i++) a[i] += b[i];
}
void operator-=(vector<ll>& a, const vector<ll>& b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < int(b.size()); i++) a[i] -= b[i];
}
vector<ll> operator*(const vector<ll>& a, const vector<ll>& b) {
  return convolution_ll(a, b);
}
vector<ll> operator/(vector<ll> a, ll b) {
  for (ll& x : a) x /= b;
  return a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<int>> g(n);
  centroid_decomposition cd(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
    cd.add_edge(a, b);
  }
  cd.build();

  vector<ll> freq;
  vector<bool> removed(n);
  for (int i = 0; i < n; i++) {
    int c = cd.dfs_order[i];
    vector<ll> fsum(1), f2sum;
    for (int j = 0; j < int(g[c].size()); j++) {
      vector<ll> f;
      auto dfs = [&](auto self, int v, int pv, int d) -> void {
        while (int(f.size()) <= d) f.push_back(0);
        f[d]++;
        for (int nv : g[v]) {
          if (!removed[nv] && nv != pv) self(self, nv, v, d + 1);
        }
      };
      if (!removed[g[c][j]]) dfs(dfs, g[c][j], c, 1);
      fsum += f;
      f2sum += f * f;
    }
    fsum[0]++;
    freq += fsum * fsum;
    freq -= f2sum;
    removed[c] = true;
  }

  freq.resize(n);
  for (int i = 1; i < n; i++) cout << freq[i] / 2 << " ";
}