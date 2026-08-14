#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "algebra/sum_affine.hpp"
#include "tree/rerooting_dp.hpp"
#include "util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;
using mint = modint998244353;
using M = alg::sum_affine<mint>;

int main() {
  int n;
  cin >> n;
  std::vector<M::S> a(n);
  rep(i, 0, n) {
    cin >> a[i].val;
    a[i].len = 1;
  }
  rerooting_dp<M> rerooting(a);
  rep(i, 0, n - 1) {
    int u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    rerooting.add_edge(u, v, {b, c});
  }
  for (auto p : rerooting.build().ans) cout << p.val << " ";
}