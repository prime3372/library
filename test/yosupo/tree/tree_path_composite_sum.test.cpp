#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "tree/rerooting_dp.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

struct S {
  mint val;
  int len;
};
S op(S x, S y) { return {x.val + y.val, x.len + y.len}; }
S e() { return {0, 0}; }
struct F {
  mint a, b;
};
S act(F f, S x) { return {f.a * x.val + f.b * x.len, x.len}; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<S> a(n);
  for (auto& ai : a) {
    cin >> ai.val;
    ai.len = 1;
  }
  rerooting_dp<S, op, e, F, act> rerooting(a);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    rerooting.add_edge(u, v, {b, c});
  }
  for (auto p : rerooting.build().ans) cout << p.val << " ";
}