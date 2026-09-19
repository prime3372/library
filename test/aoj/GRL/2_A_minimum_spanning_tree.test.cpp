#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_2_A"

#include "graph/kruscal.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  kruscal<int> g(n);
  std::vector<int> weight;
  for (int i = 0; i < m; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    g.add_edge(s, t, w);
    weight.push_back(w);
  }
  int ans = g.min();
  int w_sum = 0;
  for (int e : g.mst()) w_sum += weight[e];
  assert(w_sum == ans);
  cout << ans << "\n";
}