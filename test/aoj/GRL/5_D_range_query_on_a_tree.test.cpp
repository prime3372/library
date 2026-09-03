#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_5_D"

#include "ds/fenwick_tree.hpp"
#include "tree/euler_tour.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  euler_tour et(n);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int c;
      cin >> c;
      et.add_edge(i, c);
    }
  }
  et.build();

  int q;
  cin >> q;
  fenwick_tree<ll> fw(n);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int v;
      ll w;
      cin >> v >> w;
      fw.imos_add(et.in[v], et.out[v], w);
    } else {
      int u;
      cin >> u;
      cout << fw.imos_get(et.in[u]) << "\n";
    }
  }
}