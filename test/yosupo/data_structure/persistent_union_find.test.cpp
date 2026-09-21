#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include "ds/persistent_union_find.hpp"
#include <iostream>
#include <vector>

using namespace cp;
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<persistent_union_find::node*> past(q + 1);
  persistent_union_find uf(n);
  past[0] = uf.snapshot();
  for (int i = 1; i <= q; i++) {
    int t, k, u, v;
    cin >> t >> k >> u >> v;
    k++;
    if (t == 0) {
      uf.restore(past[k]);
      uf.unite(u, v);
      past[i] = uf.snapshot();
    } else {
      uf.restore(past[k]);
      cout << uf.same(u, v) << "\n";
    }
  }
}