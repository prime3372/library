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

template <bool directed, bool no_self_loops, bool no_multiple_edges,
          bool connected>
void test(int n, int m, int s = -1) {
  auto edges =
      random_graph<directed, no_self_loops, no_multiple_edges, connected>(n, m,
                                                                          s);

  assert(int(edges.size()) == m);

  union_find uf(n);
  vector<vector<int>> g(n);
  vector<pair<int, int>> check_edges;
  check_edges.reserve(m);

  for (auto [u, v] : edges) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    u--, v--;

    if (no_self_loops) assert(u != v);

    int cu = u, cv = v;
    if (!directed && cu > cv) swap(cu, cv);
    check_edges.emplace_back(cu, cv);

    uf.unite(u, v);
    g[u].push_back(v);
    if (!directed) g[v].push_back(u);
  }

  if (no_multiple_edges) {
    sort(check_edges.begin(), check_edges.end());
    int count_distinct = int(unique(check_edges.begin(), check_edges.end()) -
                             check_edges.begin());
    assert(count_distinct == m);
  }

  if (connected && n > 0) {
    if (!directed) {
      assert(uf.groups().size() == 1);
    } else {
      assert(s != -1);
      vector<bool> reached(n, false);
      simple_queue<int> que;
      que.push(s);
      reached[s] = true;
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

template <bool directed, bool no_self_loops, bool no_multiple_edges,
          bool connected>
void run_cases() {
  vector<pair<int, int>> cases = {
      {0, 0},           // empty
      {1, 0},           // point
      {10, 10},         // small-sparse
      {10, 100},        // small-dense
      {100, 10000},     // medium-dense
      {1000, 1500},     // medium-sparse
      {100000, 200000}  // large-sparse
  };

  for (auto [n, m] : cases) {
    if (connected && directed && n == 0) continue;
    ll max_m = directed ? (no_self_loops ? 1LL * n * (n - 1) : 1LL * n * n)
                        : (no_self_loops ? 1LL * n * (n - 1) / 2
                                         : 1LL * n * (n + 1) / 2);
    if (m > max_m) m = int(max_m);
    int s = (connected && directed) ? uniform(0, n - 1) : -1;
    test<directed, no_self_loops, no_multiple_edges, connected>(n, m, s);
  }
}

template <int mask> void run_all_combinations() {
  constexpr bool directed = (mask >> 3) & 1;
  constexpr bool no_self_loops = (mask >> 2) & 1;
  constexpr bool no_multiple_edges = (mask >> 1) & 1;
  constexpr bool connected = mask & 1;

  run_cases<directed, no_self_loops, no_multiple_edges, connected>();

  if constexpr (mask) {
    run_all_combinations<mask - 1>();
  }
}

int main() {
  run_all_combinations<16>();
  cout << "Hello World\n";
}