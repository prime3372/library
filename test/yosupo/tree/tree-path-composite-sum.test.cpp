#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include "tree/rerooting-dp.hpp"
#include "util/static-modint.hpp"
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
S mapping(F f, S x) { return {f.a * x.val + f.b * x.len, x.len}; }

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
  RerootingDP<S, op, e, F, mapping> rerooting(a);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    mint b, c;
    cin >> u >> v >> b >> c;
    rerooting.add_edge(u, v, {b, c});
  }
  rerooting.build();
  for (auto p : rerooting.ans) cout << p.val << " ";
}