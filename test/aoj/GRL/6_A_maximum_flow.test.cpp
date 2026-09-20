#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_6_A"

#include "graph/max_flow.hpp"
#include <cassert>
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  max_flow<int> mf(n);
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    mf.add_edge(u, v, c);
    edges.emplace_back(u, v, c);
  }
  int ans = mf.flow(0, n - 1);
  auto mf_edges = mf.edges();
  assert(int(mf_edges.size()) == m);
  vector<int> in(n), out(n);
  for (int i = 0; i < m; i++) {
    auto [u, v, c] = edges[i];
    auto [from, to, cap, flow] = mf_edges[i];
    assert(from == u && to == v && cap == c);
    assert(flow <= cap);
    in[to] += flow;
    out[from] += flow;
  }
  assert(in[0] == 0 && out[0] == ans);
  assert(in[n - 1] == ans && out[n - 1] == 0);
  for (int i = 1; i < n - 1; i++) assert(in[i] == out[i]);
  cout << ans << "\n";
}