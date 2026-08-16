#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include "tree/rooted_tree_hash.hpp"
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
  auto hs = t.build(0).hash;
  vector<pair<hash61, int>> hs_idx(n);
  for (int i = 0; i < n; i++) hs_idx[i] = {hs[i], i};
  sort(hs_idx.begin(), hs_idx.end());
  int id = 0;
  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    ans[hs_idx[i].second] = id;
    if (i < n - 1 && hs_idx[i].first != hs_idx[i + 1].first) id++;
  }
  cout << id + 1 << "\n";
  for (int x : ans) cout << x << " ";
}