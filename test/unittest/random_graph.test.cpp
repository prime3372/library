#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "ds/simple_queue.hpp"
#include "ds/union_find.hpp"
#include "random/engine.hpp"
#include "random/random_graph.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n, int m, random_graph_config config) {
  auto [directed, no_self_loops, no_multiple_edges, connected, one_indexed,
        start] = config;

  auto edges = random_graph(n, m, config);
  assert(int(edges.size()) == m);

  union_find uf(n);
  vector<vector<int>> g(n);

  for (auto& [u, v] : edges) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    if (no_self_loops) assert(u != v);
    if (!directed && u > v) std::swap(u, v);
    u--, v--;
    uf.unite(u, v);
    g[u].push_back(v);
    if (!directed) g[v].push_back(u);
  }

  if (no_multiple_edges) {
    sort(edges.begin(), edges.end());
    assert(unique(edges.begin(), edges.end()) == edges.end());
  }

  if (connected && n > 0) {
    if (!directed) {
      assert(uf.groups().size() == 1);
    } else {
      assert(start != -1);
      vector<bool> reached(n, false);
      simple_queue<int> que;
      que.push(start);
      reached[start] = true;
      while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int nv : g[v]) {
          if (!reached[nv]) {
            reached[nv] = true;
            que.push(nv);
          }
        }
      }
      for (int i = 0; i < n; i++) assert(reached[i]);
    }
  }
}

void run_cases(random_graph_config config) {
  constexpr pair<int, int> cases[] = {
      {0, 0},           // empty
      {1, 0},           // point
      {10, 10},         // small-sparse
      {10, 100},        // small-dense
      {100, 10000},     // medium-dense
      {1000, 1500},     // medium-sparse
      {100000, 200000}  // large-sparse
  };
  auto& [directed, no_self_loops, no_multiple_edges, connected, one_indexed,
         start] = config;

  for (auto [n, m] : cases) {
    if (connected && directed && n == 0) continue;
    ll max_m = directed ? (no_self_loops ? 1LL * n * (n - 1) : 1LL * n * n)
                        : (no_self_loops ? 1LL * n * (n - 1) / 2
                                         : 1LL * n * (n + 1) / 2);
    if (m > max_m) m = int(max_m);
    start = (connected && directed) ? uniform(0, n - 1) : -1;
    test(n, m, config);
  }
}

void run_all_combinations() {
  for (int mask = 0; mask < 16; mask++) {
    bool directed = (mask >> 0) & 1;
    bool no_self_loops = (mask >> 1) & 1;
    bool no_multiple_edges = (mask >> 2) & 1;
    bool connected = (mask >> 3) & 1;
    run_cases({directed, no_self_loops, no_multiple_edges, connected});
  }
}

int main() {
  run_all_combinations();
  cout << "Hello World\n";
}