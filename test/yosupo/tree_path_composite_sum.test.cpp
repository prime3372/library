#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "../../algebra/Sum_Affine.hpp"
#include "../../tree/rerooting_dp.hpp"
#include "../../util/static_modint.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using mint = modint998244353;
using S = typename Sum_Affine<mint>::S;
using F = typename Sum_Affine<mint>::F;

int main() {
  int n;
  cin >> n;
  std::vector<S> a(n);
  rep(i, 0, n) {
    mint ai;
    cin >> ai;
    a[i] = S{ai, 1};
  }
  rerooting_dp<Sum_Affine<mint>> rerooting(a);
  rep(i, 0, n - 1) {
    int u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    rerooting.add_edge(u, v, F{b, c});
  }
  for (S p : rerooting.build().ans) cout << p.val << " ";
}
