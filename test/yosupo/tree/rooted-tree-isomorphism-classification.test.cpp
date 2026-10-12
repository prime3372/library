#define PROBLEM \
  "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include "tree/rooted-tree-hash.hpp"
#include "util/algo-utility.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  RootedTreeHash t(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    t.add_edge(i, p);
  }
  auto hash = t.build(0).hash;
  auto ans = compress(hash);
  cout << *std::max_element(ans.begin(), ans.end()) + 1 << "\n";
  for (int x : ans) cout << x << " ";
}