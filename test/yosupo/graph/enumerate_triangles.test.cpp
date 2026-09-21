#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"

#include "graph/enumerate_triangles.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  int n, m;
  cin >> n >> m;
  vector<mint> x(n);
  for (mint& xi : x) cin >> xi;
  vector<pair<int, int>> edges(m);
  for (auto& [u, v] : edges) cin >> u >> v;
  mint ans = 0;
  for (auto [a, b, c] : enumerate_triangles(n, edges)) {
    ans += x[a] * x[b] * x[c];
  }
  cout << ans << "\n";
}