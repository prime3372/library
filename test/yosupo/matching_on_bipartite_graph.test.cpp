#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "graph/bipartite_matching.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int l, r, m;
  cin >> l >> r >> m;
  bipartite_matching bm(l, r);
  rep(i, 0, m) {
    int a, b;
    cin >> a >> b;
    bm.add_edge(a, b);
  }
  cout << bm.init() << endl;
  auto es = bm.max_matching();
  for (auto e : es) cout << e.from << " " << e.to << "\n";
}
