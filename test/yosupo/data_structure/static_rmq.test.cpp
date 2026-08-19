#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "algebra/min.hpp"
#include "ds/disjoint_sparse_table.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int& ai : a) cin >> ai;
  disjoint_sparse_table<alg::min<int, int(1e9)>> dst(a);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << dst.prod(l, r) << "\n";
  }
}