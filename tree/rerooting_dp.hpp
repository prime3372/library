#pragma once

#include <cassert>
#include <vector>

#include "algebra/monoid_with_mapping.hpp"

namespace cp {

template <monoid_with_mapping M> struct rerooting_dp {
  using S = typename M::S;
  using F = typename M::F;

public:
  rerooting_dp() : rerooting_dp(0) {}
  explicit rerooting_dp(int _n) : rerooting_dp(std::vector<S>(_n, M::e())) {}
  explicit rerooting_dp(int _n, S v) : rerooting_dp(std::vector<S>(_n, v)) {}
  explicit rerooting_dp(const std::vector<S>& v) : n(int(v.size())), g(int(v.size())), vals(v) {}

  void add_edge(int from, int to, F f) { add_edge(from, to, f, f); }
  void add_edge(int from, int to, F f, F rf) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    int from_id = int(g[from].size());
    int to_id = int(g[to].size());
    g[from].push_back(edge{to, to_id, f});
    g[to].push_back(edge{from, from_id, rf});
  }

  std::vector<std::vector<S>> dp;
  std::vector<S> ans;

  rerooting_dp& build() {
    assert(1 <= n);

    std::vector<int> par(n, -1), ord(n);
    {
      int now_ord = 0;
      auto dfs = [&](auto self, int v, int pv) -> void {
        par[v] = pv;
        ord[now_ord++] = v;
        for (edge e : g[v]) {
          if (e.to != pv) self(self, e.to, v);
        }
      };
      for (int i = 0; i < n; i++) {
        if (par[i] == -1) dfs(dfs, i, i);
      }
    }

    dp.assign(n, std::vector<S>());
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
      dp[par[v]][rev] = M::mapping(g[par[v]][rev].f, M::op(cum, vals[v]));
    }

    ans.assign(S, S());
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
        dp[to][rev] = M::mapping(g[to][rev].f, M::op(M::op(cum, rcum[j + 1]), vals[v]));
        cum = M::op(cum, dp[v][j]);
      }
      ans[v] = M::op(cum, vals[v]);
    }
    return *this;
  }

private:
  int n;
  struct edge {
    int to, rev;
    F f;
  };
  std::vector<std::vector<edge>> g;
  std::vector<S> vals;
};

} // namespace cp