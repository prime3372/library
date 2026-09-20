#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_5_A"

#include "tree/tree_diameter.hpp"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  tree_diameter<int> diam(n);
  vector<pair<int, int>> edges(n - 1);
  vector<int> weights(n - 1);
  for (int i = 0; i < n - 1; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    diam.add_edge(s, t, w);
    edges[i] = {s, t};
    weights[i] = w;
  }
  diam.build();
  int d = 0;
  auto& v = diam.vertices;
  auto& e = diam.edges;
  assert(v.size() == e.size() + 1);
  for (int i = 0; i < int(v.size()) - 1; i++) {
    assert(0 <= e[i] && e[i] < n - 1);
    d += weights[e[i]];
    auto p1 = make_pair(v[i], v[i + 1]);
    auto p2 = make_pair(v[i + 1], v[i]);
    assert(edges[e[i]] == p1 || edges[e[i]] == p2);
  }
  assert(diam.dist == d);
  cout << diam.dist << "\n";
}