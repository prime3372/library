#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "ds/fenwick-tree.hpp"
#include "tree/euler-tour.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (ll& ai : a) cin >> ai;
  EulerTour et(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    et.add_edge(i, p);
  }
  et.build();
  auto& in = et.in;
  auto& out = et.out;
  FenwickTree<ll> fw(n);
  for (int i = 0; i < n; i++) fw.add(in[i], a[i]);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int p;
      ll x;
      cin >> p >> x;
      fw.add(in[p], x);
    } else {
      int u;
      cin >> u;
      cout << fw.sum(in[u], out[u]) << "\n";
    }
  }
}