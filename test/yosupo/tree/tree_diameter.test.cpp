#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "tree/tree_diameter.hpp"
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  tree_diameter<ll> diam(n);
  vector<pair<int, int>> edges(n - 1);
  for (int i = 0; i < n - 1; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    diam.add_edge(a, b, c);
    edges[i] = {a, b};
  }
  diam.build();
  ll dist = diam.dist;
  auto v = diam.vertices, e = diam.edges;
  cout << dist << " " << v.size() << "\n";
  for (int i = 0; i < int(v.size()); i++) {
    cout << v[i] << " ";
  }
  assert(e.size() == v.size() - 1);
  for (int i = 0; i < int(v.size()) - 1; i++) {
    auto p1 = make_pair(v[i], v[i + 1]);
    auto p2 = make_pair(v[i + 1], v[i]);
    assert(edges[e[i]] == p1 || edges[e[i]] == p2);
  }
}