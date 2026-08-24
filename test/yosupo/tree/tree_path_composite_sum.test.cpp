#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "algebra/sum_affine.hpp"
#include "tree/rerooting_dp.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;
using M = alg::sum_affine<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<M::S> a(n);
  for (auto& ai : a) {
    cin >> ai.val;
    ai.len = 1;
  }
  rerooting_dp<M> rerooting(a);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    rerooting.add_edge(u, v, {b, c});
  }
  for (auto p : rerooting.build().ans) cout << p.val << " ";
}