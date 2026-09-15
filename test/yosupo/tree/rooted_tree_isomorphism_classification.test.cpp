#define PROBLEM \
  "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include "tree/rooted_tree_hash.hpp"
#include "util/algo_utility.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  rooted_tree_hash t(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    t.add_edge(i, p);
  }
  auto hash = t.build(0).hash;
  auto ans = compress(hash);
  cout << max(ans) + 1 << "\n";
  for (int x : ans) cout << x << " ";
}