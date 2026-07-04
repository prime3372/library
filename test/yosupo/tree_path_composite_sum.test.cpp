#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "../../algebra/sum_affine.hpp"
#include "../../tree/rerooting_dp.hpp"
#include "../../util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using mint = modint998244353;
using S = typename sum_affine<mint>::S;
using F = typename sum_affine<mint>::F;

int main() {
  int n;
  cin >> n;
  std::vector<S> a(n);
  rep(i, 0, n) {
    mint ai;
    cin >> ai;
    a[i] = S{ai, 1};
  }
  rerooting_dp<sum_affine<mint>> rerooting(a);
  rep(i, 0, n - 1) {
    int u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    rerooting.add_edge(u, v, F{b, c});
  }
  for (S p : rerooting.build().ans) cout << p.val << " ";
}
