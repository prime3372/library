#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "tree/tree_diameter.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  tree_diameter<ll> diam(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    diam.add_edge(a, b, c);
  }
  diam.build();
  cout << diam.len << " " << diam.vertices.size() << "\n";
  for (int v : diam.vertices) cout << v << " ";
}