#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "random/engine.hpp"
#include "random/random_tree.hpp"
#include "ds/union_find.hpp"
#include <cassert>
#include <iostream>

using namespace std;
using namespace cp;

void test(int n) {
  auto edges = random_tree(n);
  assert(int(edges.size()) == n - 1);
  union_find uf(n);
  for (auto [u, v] : edges) {
    assert(!uf.same(u, v));
    uf.unite(u, v);
  }
}
void small() { test(uniform(1, 100)); }
void large() { test(uniform(1, 100000)); }

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  for (int i = 0; i < 100000; i++) small();
  for (int i = 0; i < 500; i++) large();
  solve();
}