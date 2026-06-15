#pragma once

#include <cassert>
#include <vector>
#include "../algebra/concepts.hpp"

template <monoid M,
          class E,
          typename M::S(*put_edge)(typename M::S, E),
          typename M::S(*put_vertex)(typename M::S, int)>
struct rerooting_dp {
  using S = typename M::S;

public:
  rerooting_dp() : rerooting_dp(0) {}
  explicit rerooting_dp(int _n) : dp(_n), ans(_n), n(_n), g(_n) {}

  void add_edge(int from, int to, E weight) { add_edge(from, to, weight, weight); }
  void add_edge(int from, int to, E weight, E rweight) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    int from_id = int(g[from].size());
    int to_id = int(g[to].size());
    g[from].push_back(edge{to, to_id, weight});
    g[to].push_back(edge{from, from_id, rweight});
  }

  std::vector<std::vector<S>> dp;
  std::vector<S> ans;

  rerooting_dp& build() {
    assert(1 <= n);

    int now_ord = 0;
    std::vector<int> par(n, -1), ord(n);
    auto dfs = [&](auto self, int v, int pv) -> void {
      par[v] = pv;
      ord[now_ord++] = v;
      for (edge _e : g[v]) {
        if (_e.to != pv) self(self, _e.to, v);;
      }
    };
    for (int i = 0; i < n; i++) {
      if (par[i] == -1) dfs(dfs, i, i);
    }

    for (int v = 0; v < n; v++) {
      dp[v].resize(g[v].size());
    }
    for (int i = n - 1; i >= 0; i--) {
      int v = ord[i];
      int par_id = -1;
      S cum = M::e();
      for (int j = 0; j < int(g[v].size()); j++) {
        if (g[v][j].to == par[v]) {
          par_id = j;
          continue;
        }
        cum = M::op(cum, dp[v][j]);
      }
      if (par_id == -1) continue;
      int rev = g[v][par_id].rev;
      dp[par[v]][rev] = put_edge(put_vertex(cum, v), g[par[v]][rev].w);
    }

    for (int i = 0; i < n; i++) {
      int v = ord[i];
      std::vector<S> rcum(g[v].size() + 1);
      rcum[g[v].size()] = M::e();
      for (int j = int(g[v].size()); j >= 1; j--) {
        rcum[j - 1] = M::op(rcum[j], dp[v][j - 1]);
      }

      S cum = M::e();
      for (int j = 0; j < int(g[v].size()); j++) {
        int to = g[v][j].to, rev = g[v][j].rev;
        dp[to][rev] = put_edge(put_vertex(M::op(cum, rcum[j + 1]), v),
                                          g[to][rev].w);
        cum = M::op(cum, dp[v][j]);
      }
      ans[v] = put_vertex(cum, v);
    }
    return *this;
  }

private:
  int n;
  struct edge {
    int to, rev;
    E w;
  };
  std::vector<std::vector<edge>> g;
};
