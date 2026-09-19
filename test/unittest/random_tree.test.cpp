#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "random/random_tree.hpp"
#include "ds/union_find.hpp"
#include <cassert>
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n) {
  auto edges = random_tree(n);
  assert(int(edges.size()) == n - 1);
  union_find uf(n);
  for (auto [u, v] : edges) {
    assert(!uf.same(u - 1, v - 1));
    uf.unite(u - 1, v - 1);
  }
}
void large() { test(uniform(1, 100000)); }
void small() { test(uniform(1, 10)); }

int main() {
  for (int i = 0; i < 10; i++) large();
  for (int i = 0; i < 1000; i++) small();
  cout << "Hello World\n";
}